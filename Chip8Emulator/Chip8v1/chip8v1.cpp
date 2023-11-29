#include<iostream>
#include<stack>
#include"chip8.h"
#include<fstream>

#define MEMSIZE 4096
#define REGSIZE 16
#define STARTADDRESS 0x200
#define VIDEO_HEIGHT 32
#define VIDEO_WIDTH 64

// Load the rom
void Chip8::loadRom(char const* filename){
	//// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	
	if(file.is_open()){
		// Get the size of the file and allocate a place to hold contents
		std::streampos size = file.tellg();
		char* buffer = new char[size]; // THIS WILL BE LOADED INTO MEM
		
		// Go back to beginning of the file and fill the buffer
		file.seekg(0,std::ios::beg);
		file.read(buffer, size);
		file.close();
		
		// LOAD THE BUFFER U CREATED INTO MEMORY
		for(long i = 0; i < size; i++){
			memory[STARTADDRESS + i] = buffer[i];
		}
		
		// delete buffer
		delete[] buffer;
	}
}

//FONTS
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// CONSTRUCTOR
Chip8::Chip8(){
	// SET PROGRAM COUNTER TO BEGINNING OF PROGRAM
	programCounter = STARTADDRESS;
	
	// LOAD THE FONTSET INTO MEMORY
	for(unsigned int i = 0; i < FONTSET_SIZE; ++i){
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}
}



// INSTRUCTION SETS
void Chip8::instructionCPU(const uint8_t instHex){
	//programCounter += 2; // Increment counter by 2
	
	// GRAB 0XY0 OF INSTRUCTIONS
	const uint8_t x = (instHex & 0x0F00) >> 8;
	const uint8_t y = (instHex & 0x00F0) >> 4;
	
	switch(instHex & 0xF000){
		default:
			break;
		case 0x0000: // 
			switch(instHex & 0xFFFF){
				case 0x00E0: //CLS
					// Clear screen
					// Set all items in video[] to 0
					for(int i = 0; i < 64*32; i++){
						video[i] = 0;
					}
					std::cout << "0xCLS\n";
					break;
				case 0x00EE: // RET
					std::cout << "HERE 0x00EE\n";
					if(!levelStack.empty()){
						levelStack.pop();
					}
					//levelStack.pop(); // Pop the stack
					std::cout << "0x00EE\n";
					break;
			}
			break;
		case 0x1000: // JP addr 1NNN
			std::cout << "HERE 0x1000\n";
			programCounter = instHex & 0x0FFF;
			std::cout << "0x1000\n";
			break;
		
		case 0x2000: // CALL addr
			levelStack.push(programCounter);
			programCounter = instHex & 0x0FFF;
			break;
		case 0x6000:// set 6XNN
			std::cout << "0x6000\n";
			reg[x] = instHex & 0x00FF;
			break;
		case 0x7000: // 7XNN: Add the value NN to VX. 
			std::cout << "0x7000\n";
			reg[x] += instHex & 0x00FF;
			break;
		case 0xA000: // ANNN: set index register to value NNN
			std::cout << "0xA000\n";
			indexReg = instHex & 0x0FFF;
			break;
		case 0xD000: // DXYN DISPLAY
			std::cout << "HERE DXYN\n";
			uint8_t Vx = (instHex & 0x0F00u) >> 8u;
			uint8_t Vy = (instHex& 0x00F0u) >> 4u;
			uint8_t height = instHex & 0x000Fu;

			// Wrap if going beyond screen boundaries
			uint8_t xPos = reg[Vx] % VIDEO_WIDTH;
			uint8_t yPos = reg[Vy] % VIDEO_HEIGHT;

			reg[0xF] = 0;

			for (unsigned int row = 0; row < height; ++row)
			{
				uint8_t spriteByte = memory[indexReg + row];

				for (unsigned int col = 0; col < 8; ++col)
				{
					uint8_t spritePixel = spriteByte & (0x80u >> col);
					uint32_t* screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

					// Sprite pixel is on
					if (spritePixel)
					{
						// Screen pixel also on - collision
						if (*screenPixel == 0xFFFFFFFF)
						{
							reg[0xF] = 1;
						}

						// Effectively XOR with the sprite pixel
						*screenPixel ^= 0xFFFFFFFF;
					}
				}		
			}
			//std::cout << "DXYN\n";
			break;
	}

}


void Chip8::cycle(){
		// Fetch
	opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];
	//uint8_t test = memory[programCounter];
	//std::cout << test << '\n';
	
	// Increment the PC before we execute anything
	programCounter += 2;

	// Decode and Execute
	//instructionCPU(opcode);
	//uint8_t test = 0xD;
	instructionCPU(opcode >> 12u);
	// Decrement the delay timer if it's been set
	if(delayTimer > 0)
	{
		--delayTimer;
	}

	// Decrement the sound timer if it's been set
	if(soundTimer > 0)
	{
		--soundTimer;
	}
	//draw();
}


void Chip8::draw(){
	int i = 0;
	for(int y = 0; y < VIDEO_HEIGHT; y++){
		for(int x = 0; x < VIDEO_WIDTH;x++){
			if(video[i] > 0){
				std::cout << "#";
			}
			else{
				std::cout << " ";
			}
			i++;
		}
		std::cout << std::endl;
	}

}
