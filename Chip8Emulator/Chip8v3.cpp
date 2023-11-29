#include"Chip8.h"
#include<iostream>
#include<fstream>
#include<ios>
#include<stack>
#include<random>

#define STARTADDRESS 0x200

void Chip8::load(){
	for(int i = 0; i < (SCREENHEIGHT*SCREENWIDTH); i++){
		video[i] = 0;
	}
	pc = STARTADDRESS;
	const unsigned int FONTSET_SIZE = 80;
	const unsigned int FONTSET_START_ADDRESS = 0x50;

	// CREATE FONT ARRAY WITH THE FONT SPRITES
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
	// LOAD INTO MEMORY
	// LOAD THE FONTSET INTO MEMORY
	for(long i = 0; i < FONTSET_SIZE; ++i){
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}
	
	//opening file/ creating file object with binary perameters
	std::ifstream File ("IBM.ch8", std::ios::in | std::ios::binary);
	//Get size of the file
	File.seekg(0, std::ios::end);
	int size = File.tellg();
	File.seekg(0, std::ios::beg);
	
	//Create temp buffer
	char *buffer = new char[size];
	File.read(buffer, size);
	
	// LOAD THE BUFFER U CREATED INTO MEMORY
	for(int i = 0; i < size; i++){
		memory[STARTADDRESS + i] = buffer[i];
	}
	
	delete[] buffer;
	File.close();
		
}


void Chip8::cycle(){
		
		// GET OPCODE FROM MEMORY
		opcode = (memory[pc] << 8u) | memory[pc+1];
		// INCREMENT PROGRAMCOUNTER
		pc+=2;
		// SEND OPCODE TO CPU
		cpu(opcode);
		
		if(soundTimer > 0) soundTimer--;
		if(delayTimer > 0) delayTimer--;
}

void Chip8::cpu(uint16_t hexa){
	const uint8_t x = (hexa & 0x0F00) >> 8;
	const uint8_t y = (hexa & 0x00F0) >> 4;
	uint8_t temp = v[x];
	switch(hexa & 0xF000){
		case 0x0000:
			switch(hexa & 0xFFFF){
				case 0x00E0: // CLS , Clear screen
					if(int i = 0; i < SCREENHEIGHT*SCREENHEIGHT){
						video[i] = 0;
					}
					break;
				case 0x00EE: // RET
					lStack.pop();
					break;
			}
			break;
		case 0x1000: //1NNN JP ADDR
			pc = opcode & 0x0FFF;
			break;
		case 0x2000: // CALL addr 2nnn
			lStack.push(pc);
			pc = hexa & 0x0FFF;
			break;
		case 0x3000: // SE VX, Byte 3XKK
			if(v[x] ==  hexa&0x00FF){
				pc +=2;
			}
			break;
		case 0x4000: // SNE Vx, Byte 4XKK
			if(v[x] != hexa&0x00FF){
				pc += 2;
			}
			break;
		case 0x5000: // SE VX, VY 5XY0
			if(v[x] == v[y]){
				pc += 2;
			}
			break;
		case 0x6000: // 6XNN SET REGISTER TO VX
			v[x] = hexa & 0x00FF;
			break;
		case 0x7000: // ADD VALUE TO REGISTER 7XNN
			v[x] += hexa & 0x00FF;
			break;
		case 0x8000: // GOTTA DO MORE CHECKING
			switch(hexa &0xF00F){
				case 0x8000: // LD VX, VY 8XY0
					v[x] = v[y];
					break;
				case 0x8001: // OR VX, VY 8XY1
					v[x] = v[x] | v[y];
					break;
				case 0x8002: // AND VX, VY 8XY2
					v[x] = v[x] & v[y];
					break;
				case 0x8003: // XOR VX, VY 8XY3
					v[x] = v[x] ^ v[y];
					break;
				case 0x8004: // ADD VX VY 8XY4
					// IF SIZE GREATER THEN 8bits set v[F] to 1 otherwise 0
					v[0xF] = 0;
					if((v[x] + v[y]) > 255){
						v[0xF] = 1;
					}
					v[x] = (v[x]+v[y]) & 0x00FF;
					break;
				case 0x8005: // SUB VX, VY 
					v[0xF] = 0;
					if(v[x] > v[y]){
						v[0xF] = 1;
					}
					v[x] = v[x] - v[y];
					break;
				case 0x8006: // SHR VX {, VY}
					//uint8_t Vx1 = (hexa &0x0F00) >> 8;
					v[0xF] = v[(hexa &0x0F00)>>8] & 0x1;
					v[(hexa&0x0F00)>>8] >>=1;
					break;
				case 0x8007: // SUBN VX, VY 8XYN
					v[0xF] = 0;
					if(v[x] > v[y]){
						v[0xF] = 1;
					}
					v[x] = v[y] - v[x];
					break;
				case 0x800E: // SHL VX {, VY} 
					//uint8_t VX = (opcode & 0x0F00) >> 8;
					// Save MSB in VF
					//v[0xF] = (v[VX] & 0x80) >> 7;
					//v[VX] <<= 1;
					break;
			}
			break;
		case 0x9000: // SNE VX, VY 9XY0
			if(v[x] != v[y]){
				pc+=2;
			}
			break;
		case 0xA000: // SET INDEX REG TO ANNN
			indexReg = hexa & 0x0FFF;
			break;
		case 0xB000: // JP V0, Addr Bnnn
			pc = (hexa &0x0FFF) + v[0];
			break;
		case 0xC000: // RND VX, BYTE CXKK
			//random CODE
			// SET Vx + RANDOM BYTE AND kk
			v[x] = (rand() % 255) + (hexa & 0x00FF);
			break;
		case 0xE000:
			switch(hexa &0xF0FF){
				case 0xE09E:
					// Skip next instruction if key of value v[x] is pressed
					break;
				case 0xE0A1:
					//Skip next instruction if key of value v[x] is not pressed
					break;
			}
			break;
		case 0xF000:
			switch(hexa &0xF0FF){
				case 0xF007: // FX07 LD VX, DT
					v[x] = delayTimer;
					break;
				case 0xF00A: // LD VX K
					// Wait for key press, store the value of key in v[x]
					break;
				case 0xF015: // LD DT VX
					delayTimer = v[x];
					break;
				case 0xF018: // LD SET VX
					soundTimer = v[x];
					break;
				case 0xF01E: // ADD I VX
					indexReg = indexReg + v[x];
					break;
				case 0xF029: // LD F VX
					indexReg = 5 * (v[x]);
					break;
				case 0xF033: // LD B VX
					//ones place
					memory[indexReg+2] = temp % 10;
					temp /= 10;
					// Tenth place 
					memory[indexReg+1] = temp % 10; 
					temp /= 10;
					// Hundreds
					memory[indexReg] = temp % 10;
					break;
				case 0xF055: // LD [I] VX
					for(int i = 0; i < x; i++){
						memory[indexReg+i] = v[i];
					}
					break;
				case 0xF065: // LD VX , [I]
					for(int i = 0; i < x; i++){
						v[i] = memory[indexReg+i];
					}
					break;
			}
			break;
		case 0xD000: // DXYN DISPLAY
			int8_t Vx = (hexa & 0x0F00u) >> 8u;
			uint8_t Vy = (hexa& 0x00F0u) >> 4u;
			uint8_t height = hexa & 0x000Fu;

			// Wrap if going beyond screen boundaries
			uint8_t xPos = v[Vx] % SCREENWIDTH;
			uint8_t yPos = v[Vy] % SCREENHEIGHT;

			v[0xF] = 0;

			for (unsigned int row = 0; row < height; ++row)
			{
				uint8_t spriteByte = memory[indexReg + row];

				for (unsigned int col = 0; col < 8; ++col)
				{
					uint8_t spritePixel = spriteByte & (0x80u >> col);
					uint32_t* screenPixel = &video[(yPos + row) * SCREENWIDTH + (xPos + col)];

					// Sprite pixel is on
					if (spritePixel)
					{
						// Screen pixel also on - collision
						if (*screenPixel == 0xFFFFFFFF)
						{
							v[0xF] = 1;
						}

						// Effectively XOR with the sprite pixel
						*screenPixel ^= 0xFFFFFFFF;
					}
				}		
			}
			break;
			
	}
}


// DRAW TO SCREEN FUNCTION
void Chip8::draw(){
		int i = 0;
		for(int y = 0; y < SCREENHEIGHT; y++){
			for(int x = 0; x < SCREENWIDTH; x++){
				if(video[i] != 0){
					std::cout << "#";
				}
				else{
					std::cout<< " ";
				}
				i++;
			}
			std::cout << "\n";
		}
}
