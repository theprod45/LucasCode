#include<iostream>
#include<stack>

#define MEMSIZE 4096
#define REGSIZE 16

class Chip8{
	public:
	
		Chip8();
		
		uint8_t opcode;
		//INSTRUCTION NAME
		uint8_t inst;
		// MEMORY
		// Create Array of 8bit data the size of 4096
		uint8_t memory[MEMSIZE]{};
	
		//REGISTERS
		uint8_t reg[REGSIZE]; // CREATES 16 8-bit CPU registers
	
		uint16_t programCounter; // Creates 16bit program counter 
		uint16_t indexReg; // Creates 16bit index register
	
		std::stack<uint16_t> levelStack; // Used for functions and subroutines and to return from then
	
		// TIMERS
		uint8_t delayTimer;
		uint8_t soundTimer;
	
		// KEYPAD
		uint8_t keypad[16];
		
		// VIDEO
		uint32_t video[64*32];
		void draw();
		
		
		// Load rom into memory
		void loadRom(char const* filename);
		
		// Interpret instruction
		void instructionCPU(const uint8_t instHex);
		
		// CPU 
		void cycle();
		
};

