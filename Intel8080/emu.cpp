/*
 * Intel 8080 Emulator
 * Created By Lucas Norpchen
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>


class CPU{
	public:
	CPU() { pc = 0; } // Set Program Counter to beginning of program
	uint16_t memory[0xFFFF]; // INTEL 8080 has 0xFFFF memory size 64KB
	uint16_t romSize;
	uint16_t pc; // Program Counter
	uint16_t sp; // Stack Pointer
	
	//std::stack<uint8_t> lStack;
	
	uint8_t A, B, C, D, E, H, L; // CPU REGISTERS, STARTING WITH ACCUMULATOR
	uint8_t S, Z, AC, P, CY; // CPU FLAGS
	
	uint8_t interuptFlag;
	
	void loadMemIntoRom(char* fileName, int size);
	void cycle();
	uint16_t execute(uint16_t opcode);
	
	bool parity(uint8_t x, uint8_t y);
	
};

int main(/*int argc, char** fileName*/){
	// Create file OBJ, get stream from File in binary
	//std::string inFile = fileName[1];
	std::ifstream File ("cpudiag.bin", std::ios::in | std::ios::binary);
	// ERROR NO FILE
	if(!File){
		printf("ERROR: Couldnt open file!\n");
		exit(0);
	}
	
	//Get size of the file
	File.seekg(0, std::ios::end);
	int size = File.tellg();
	File.seekg(0, std::ios::beg);
	
	//Create temp buffer
	char *buffer = new char[size];
	File.read(buffer, size);
	
	// CREATE CPU OBJ
	CPU Computer;
	
	// LOAD ROM INTO MEM
	Computer.loadMemIntoRom(buffer,size);
	delete[] buffer;
	File.close();
	
	// START CYCLE
	Computer.cycle();
	

}

uint16_t CPU::execute(uint16_t opcode){
	uint16_t optBytes = 1; // MEMORY IS CODED IN 16 BITS BUT THE OPCODES ARE 8-BIT SO ACT LIKE THESE ARE 8-BIT
	uint16_t opcode1 = memory[(pc+1)] & 0x00FF;
	uint16_t opcode2 = memory[(pc+2)] & 0x00FF;
	
	
	//printf("%02x  \n", opcode);
	switch(opcode){
		default:
			break;
		// NOP and *NOP
		case 0x00: // NOP : DO NOTHING, USE 4 CPU CYCLES
		case 0x10: // *NOP
		case 0x20: // *NOP
		case 0x30: // *NOP
		case 0x08: // *NOP
		case 0x18: // *NOP
		case 0x28: // *NOP
		case 0x38: // *NOP
			break;
		// IN AND OUT
		case 0xD3: // OUT
		case 0xDB: // IN
			break;
		// EI AND DI
		case 0xFB: // EI : ENABLE interuptFlag
			interuptFlag = 1;
			break;
		case 0xF3: // DI : DISABLE interuptFlag
			interuptFlag = 0;
			break;
		// HLT : Halts code
		case 0x76:
			printf("A:%02x  \n", A);
			printf("B:%02x  \n", B);
			printf("C:%02x  \n", C);
			printf("D:%02x  \n", D);
			printf("E:%02x  \n", E);
			printf("H:%02x  \n", H);
			printf("L:%02x  \n", L);
			printf("S:%01x Z:%01x AC:%01x P:%01x CY:%01x\n", S,Z,AC,P,CY);
			exit(0);
			break;
		// SUB
		case 0x90: // SUB B
		// ZERO
			Z = ( (( A - B ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - B ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - B ) > 0xFF);
			// PARITY FLAG
			P = parity(A,B);
			// SET A
			A = ( A - B ) & 0xFF;
			break;
		case 0x91: // SUB C
			// ZERO
			Z = ( (( A - C ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - C ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - C ) > 0xFF);
			// PARITY FLAG
			P = parity(A,C);
			// SET A
			A = ( A - C ) & 0xFF;
			break;
		case 0x92: // SUB D
			// ZERO
			Z = ( (( A - D ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - D ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - D ) > 0xFF);
			// PARITY FLAG
			P = parity(A,D);
			// SET A
			A = ( A - D ) & 0xFF;
			break;
		case 0x93: // SUB E
			// ZERO
			Z = ( (( A - E ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - E ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - E ) > 0xFF);
			// PARITY FLAG
			P = parity(A,E);
			// SET A
			A = ( A - E ) & 0xFF;
			break;
		case 0x94: // SUB H
			// ZERO
			Z = ( (( A - H ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - H ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - H ) > 0xFF);
			// PARITY FLAG
			P = parity(A,H);
			// SET A
			A = ( A - H ) & 0xFF;
			break;
		case 0x95: // SUB L
			// ZERO
			Z = ( (( A - L ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - L ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - L ) > 0xFF);
			// PARITY FLAG
			P = parity(A,L);
			// SET A
			A = ( A - L ) & 0xFF;
			break;
		case 0x96: // SUB M
			//memory[ ( H << 8 ) | L ]
			// ZERO
			Z = ( (( A - ( memory[( H << 8) | L ] ) ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - ( memory[( H << 8) | L ] ) ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - ( memory[( H << 8) | L ] ) ) > 0xFF);
			// PARITY FLAG
			P = parity(A,( memory[( H << 8) | L ] ));
			// SET A
			A = ( A - ( memory[( H << 8) | L ] ) ) & 0xFF;
			break;
		case 0x97: // SUB A
			// ZERO
			Z = ( (( A - A ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - A ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - A ) > 0xFF);
			// PARITY FLAG
			P = parity(A,A);
			// SET A
			A = ( A - A ) & 0xFF;
			break;
		case 0xDE: //SBI byte : SUB opcode1 from A
			// ZERO
			Z = ( ((A-opcode1) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A - opcode1 ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A - opcode1 ) > 0xFF);
			// PARITY FLAG
			P = parity(A,opcode1);
			// SET A
			A = ( A - opcode1 ) & 0xFF;
			optBytes = 2;
			break;
		case 0x80: // ADD B: ADD B TO A
			// ZERO
			Z = ( (( A + B ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + B ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + B ) > 0xFF);
			// PARITY FLAG
			P = parity(A,B);
			// SET A
			A = ( A + B ) & 0xFF;
			break;
		case 0x81: // ADD C
			// ZERO
			Z = ( (( A + C ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + C ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + C ) > 0xFF);
			// PARITY FLAG
			P = parity( A, C );
			// SET A
			A = ( A + C ) & 0xFF;
			break;
		case 0x82: // ADD D
			// ZERO
			Z = ( (( A + D ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + D ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + D ) > 0xFF);
			// PARITY FLAG
			P = parity( A, D );
			// SET A
			A = ( A + D ) & 0xFF;
			break;
		case 0x83: // ADD E
			// ZERO
			Z = ( (( A + E ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + E ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + E ) > 0xFF);
			// PARITY FLAG
			P = parity( A, E );
			// SET A
			A = ( A + E ) & 0xFF;
			break;
		case 0x84: // ADD H
			// ZERO
			Z = ( (( A + H ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + H ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + H ) > 0xFF);
			// PARITY FLAG
			P = parity( A, H );
			// SET A
			A = ( A + H ) & 0xFF;
			break;
		case 0x85: // ADD L
			// ZERO
			Z = ( (( A + L ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + L ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + L ) > 0xFF);
			// PARITY FLAG
			P = parity( A, L );
			// SET A
			A = ( A + L ) & 0xFF;
			break;
		case 0x86: // ADD M
			//memory[ ( H << 8 ) | L ]
			// ZERO
			Z = ( (( A + ( memory[( H << 8) | L ] ) ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + ( memory[( H << 8) | L ] ) ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + ( memory[( H << 8) | L ] ) ) > 0xFF);
			// PARITY FLAG
			P = parity(A,( memory[( H << 8) | L ] ));
			// SET A
			A = ( A + ( memory[( H << 8) | L ] ) ) & 0xFF;
			break;
		case 0x87: // ADD A
			// ZERO
			Z = ( (( A + A ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + A ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + A ) > 0xFF);
			// PARITY FLAG
			P = parity( A, A );
			// SET A
			A = ( A + A ) & 0xFF;
			break;
		case 0xC6: //ADI byte : ADD opcode1 to A
			// ZERO
			Z = ( ((A+opcode1) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A + opcode1 ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A + opcode1 ) > 0xFF);
			// PARITY FLAG
			P = parity(A,opcode1);
			// SET A
			A = ( A + opcode1 ) & 0xFF;
			optBytes = 2;
			break;
		case 0xA0: // ANA B
			// ZERO
			Z = ( (( A & B ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & B ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & B ) > 0xFF);
			// PARITY FLAG
			P = ((A & B) % 2);
			// SET A
			A = ( A & B );
			break;
		case 0xA1: // ANA C
			// ZERO
			Z = ( (( A & C ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & C ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & C ) > 0xFF);
			// PARITY FLAG
			P = ((A & C) % 2);
			// SET A
			A = ( A & C );
			break;
		case 0xA2: // ANA D
			// ZERO
			Z = ( (( A & D ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & D ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & D ) > 0xFF);
			// PARITY FLAG
			P = ((A & D) % 2);
			// SET A
			A = ( A & D );
			break;
		case 0xA3: // ANA E
			// ZERO
			Z = ( (( A & E ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & E ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & E ) > 0xFF);
			// PARITY FLAG
			P = ((A & E) % 2);
			// SET A
			A = ( A & E );
			break;
		case 0xA4: // ANA H
			// ZERO
			Z = ( (( A & H ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & H ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & H ) > 0xFF);
			// PARITY FLAG
			P = ((A & H) % 2);
			// SET A
			A = ( A & H );
			break;
		case 0xA5: // ANA L
			// ZERO
			Z = ( (( A & L ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & L ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & L ) > 0xFF);
			// PARITY FLAG
			P = ((A & L) % 2);
			// SET A
			A = ( A & L );
			break;
		case 0xA6: // ANA M
			// ZERO
			Z = ( (( A & ( memory[( H << 8) | L ] ) ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & ( memory[( H << 8) | L ] ) ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A * ( memory[( H << 8) | L ] ) ) > 0xFF);
			// PARITY FLAG
			P = ((A & ( memory[( H << 8) | L ] )) % 2);
			// SET A
			A = ( A & ( memory[( H << 8) | L ] ) );
			break;
		case 0xAA: // ANA A
			// ZERO
			Z = ( (( A & A ) & 0xFF) == 0 );
			// BIT 7 IS ON
			S = (( A & A ) &0x80 != 0);
			// // CARRY FLAG
			CY = (( A & A ) > 0xFF);
			// PARITY FLAG
			P = ((A & A) % 2);
			// SET A
			A = ( A & A );
			break;
		case 0x03: // INX B
			C++;
			if(C==0) B++;
			break;
		case 0x13: // INX D
			E++;	
			if(E==0) D++;
			break;
		case 0x23: // INX H
			L++;
			if(L==0) H++;
			break;
		case 0x33: // INX SP
			sp++;
			break;
		case 0x56:	//MOV D,M
			D = memory[ ( H << 8 ) | L ];
			break;
		case 0x5e:	//MOV E,M
			E = memory[ ( H << 8 ) | L ];
			break;
		case 0x66:	//MOV H,M
			H = memory[ ( H << 8 ) | L ];
			break;
		case 0x6f:	//MOV L,A
			L = A;
			break;
		case 0x77:	//MOV M,A
			memory[ ( H  << 8 ) | L ] = A;
			break;
		case 0x7a:	//MOV A,D
			A = D;
			break;
		case 0x7b:	//MOV A,E
			A = E;
			break;
		case 0x7c:	//MOV A,H
			A = H;
			break;
		case 0x7e:	//MOV A,M
			A = memory[ ( H << 8 ) | L ];
			break;
		// MVI 
		case 0x06: // MVI B
			B = opcode1;
			optBytes = 2;
			break;
		case 0x16: // MVI D
			D = opcode1;
			optBytes = 2;
			break;
		case 0x26: // MVI H
			H = opcode1;
			optBytes = 2;
			break;
		case 0x36: // MVI M
			memory[ ( H << 8 ) | L ] = opcode1;
			optBytes = 2;
			break;
		case 0x0E: // MVI C
			C = opcode1;
			optBytes = 2;
			break;
		case 0x1E: // MVI E
			E = opcode1;
			optBytes = 2;
			break;
		case 0x2E: // MVI L
			C = opcode1;
			optBytes = 2;
			break;
		case 0x3E: // MVI A
			A = opcode1;
			optBytes = 2;
			break;
		// LXI 
		case 0x01: // LXI B
			B = opcode2;
			C = opcode1;
			optBytes = 3;
			break;
		case 0x11: // LXI D
			D = opcode2;
			E = opcode1;
			optBytes = 3;
			break;
		case 0x21: // LXI H
			H = opcode2;
			L = opcode1;
			optBytes = 3;
			break;
		case 0x31: // LXI SP
			sp = (opcode2 << 8) | opcode1;
			optBytes = 3;
			break;
		// STA
		case 0x32: // STA 2bytes
			memory[(opcode2 << 8) | opcode1] = A;
			optBytes = 3;
			break;
		// JMP ADDRESS
		case 0xC3: // JMP address
			pc = (opcode2 << 8) | opcode1;
			//optBytes = 3;
			break;
		// JNZ jump if zero
		case 0xC2: // JNZ address
			if(Z == 0){
				pc = (opcode2 << 8) | opcode1;
			}
			else{
				optBytes = 3;
			}
			break;
		case 0xC9: // RET 
			pc = memory[sp] | (memory[sp+1] << 8);
			sp += 2;
			break;
// CHECK FOR BUGS AT CALL
		// POP 
		case 0xC1: // POP B
			C = memory[sp];
			B = memory[sp+1];
			sp +=2;
			break;
		case 0xD1: // POP D
			E = memory[sp];
			D = memory[sp+1];
			sp +=2;
			break;
		case 0xE1: // POP H
			L = memory[sp];
			H = memory[sp+1];
			sp +=2;
			break;
		// PUSH
		case 0xC5: // PUSH B
			memory[sp-1] = B;
			memory[sp-2] = C;
			sp -=2;
			break;
		case 0xD5: // PUSH D
			memory[sp-1] = D;
			memory[sp-2] = E;
			sp -=2;
			break;
		case 0xE5: // PUSH H
			memory[sp-1] = H;
			memory[sp-2] = L;
			sp -=2;
			break;
		case 0xF9: // SPHL , SP = HL
			sp = (H << 8) | L;
			break;
		case 0xE3: // XTHL, exchanges SP and HL
			// 
			break;
		
		
		
	}
	return optBytes;
}

bool CPU::parity(uint8_t x, uint8_t y){
	return (( x + y ) % 2 == 0);
}

void CPU::cycle(){
	// pc < romSize
	while(pc < romSize){
		pc += execute(memory[pc] & 0x00FF);
	}
	printf("A:%02x  \n", A);
	printf("B:%02x  \n", B);
	printf("C:%02x  \n", C);
	printf("D:%02x  \n", D);
	printf("E:%02x  \n", E);
	printf("H:%02x  \n", H);
	printf("L:%02x  \n", L);
	printf("S:%01x Z:%01x AC:%01x P:%01x CY:%01x\n", S,Z,AC,P,CY);

}


void CPU::loadMemIntoRom(char* fileName, int size){
		// LOAD ROM STARTING AT 0 to 0x2000
		for(int i = 0; i < size; i++){
			memory[i] = fileName[i];
		}
		romSize = size;
}
