#include<iostream>
#include<stack>

#define MEMORYSIZE 4096
#define SCREENWIDTH 64
#define SCREENHEIGHT 32

class Chip8{
		public:
			uint16_t opcode;
			// CREATE 4kb of memory
			uint8_t memory[MEMORYSIZE];
			// DISPLAY ARRAY
			uint32_t video[SCREENWIDTH*SCREENHEIGHT];
			// PROGRAM COUNTER 16bit
			uint16_t pc;
			// INDEX REGISTER 16bit
			uint16_t indexReg;
			// 16 level stack
			std::stack<uint16_t> lStack;
			// 16 registers 8-bit each
			uint8_t v[16];
			// TIMERS
			uint8_t delayTimer;
			uint8_t soundTimer;
		
			// LOAD ROM SPRITES AND FONT INTO MEMORY
			void load();
		
			//CPU Cycle
			void cycle();
			void cpu(uint16_t opcode);
			
			// DRAW TO SCREEN FUNCTION
			void draw();

};
