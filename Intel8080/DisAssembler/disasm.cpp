/*
	Intel 8080 Disassembler
	* Created by Lucas Norpchen
	* 09/12/22
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
int disAsm(char *buffer, int pc);

int main(int argc, char** fileName){
		//opening file/ creating file object with binary perameters
		//std::string filen = fileName;
		std::string inFile = fileName[1];
		std::ifstream File (inFile, std::ios::in | std::ios::binary);
		//FILE *f = fopen(argv[0], "rb");
		
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
		
		// Program Counter
		int pc = 0;
		while(pc < size){
			// DISASM
			pc += disAsm(buffer, pc);
		}
		
		
		File.close();
		delete[] buffer;
}

int disAsm(char *buffer, int pc){
	int optBytes = 1;
	printf("%04x  ", pc);
	unsigned char opcode = buffer[pc];
	unsigned char opcode1 = buffer[pc+1];
	unsigned char opcode2 = buffer[pc+2];
	
	switch(opcode){
		default:
			printf("INVALID OPCODE 0x%02x  \n", opcode);
			break;
			
		case 0x00: printf("NOP\n"); break; 
		case 0x10:
		case 0x20:
		case 0x30:
		case 0x08:
		case 0x18:
		case 0x28:
		case 0x38:
			printf("*NOP\n"); break; 
			
		case 0x01:
			printf("LXI B, 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x02: printf("STAX B\n"); break;
		case 0x03: printf("INX B\n"); break;
		case 0x04: printf("INR B\n"); break;
		case 0x05: printf("DCR B\n"); break;
		case 0x06:
			printf("MVI B, 0x%02x\n",opcode1);
			optBytes = 2;
			break;
		case 0x07: printf("RLC\n"); break;
		// 0x08
		case 0x09: printf("DAD B\n"); break;
		// 0x10
		case 0x0A: printf("LDAX B\n"); break;
		case 0x0B: printf("DCX B\n"); break;
		case 0x0C: printf("INR C\n"); break;
		case 0x0D: printf("DCR C\n"); break;
		case 0x0E:
			printf("MVI C, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x0F: printf("RRC\n"); break;
		// 0x10
		case 0x11:
			printf("LXI B, 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x12: printf("STAX D\n"); break;
		case 0x13: printf("INC D\n"); break;
		case 0x14: printf("INR D\n"); break;
		case 0x15: printf("DCR D\n"); break;
		case 0x16:
			printf("MVI D, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x17: printf("RAL\n"); break;
		// 0x18
		case 0x19: printf("DAD D\n"); break;
		case 0x1A: printf("LDAX D\n"); break;
		case 0x1B: printf("DCX D\n"); break;
		case 0x1C: printf("INR E\n"); break;
		case 0x1D: printf("DCR E\n"); break;
		case 0x1E:
			printf("MVI E, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x1F: printf("RRC\n"); break;
		// 0x20
		case 0x21:
			printf("LXI H, 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x22:
			printf("SHLD 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x23: printf("INX H\n"); break;
		case 0x24: printf("INR H\n"); break;
		case 0x25: printf("DCR H\n"); break;
		case 0x26:
			printf("MVI H, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x27: printf("DAA\n"); break;
		//0x28
		case 0x29: printf("DAD H\n"); break;
		case 0x2A:
			printf("LHLD 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x2B: printf("DCX H\n"); break;
		case 0x2C: printf("INR L\n"); break;
		case 0x2D: printf("DCR L\n"); break;
		case 0x2E:
			printf("MVI L, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x2F: printf("CMA\n"); break;
		// 0x30
		case 0x31:
			printf("LXI SP, 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x32:
			printf("STA 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x33: printf("INX SP\n"); break;
		case 0x34: printf("INR M\n"); break;
		case 0x35: printf("DCR M\n"); break;
		case 0x36:
			printf("MVI M, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x37: printf("STC\n"); break;
		//0x38
		case 0x39: printf("DAD SP\n"); break;
		case 0x3A:
			printf("LDA 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0x3B: printf("DCX SP\n"); break;
		case 0x3C: printf("INR A\n"); break;
		case 0x3D: printf("DCR A\n"); break;
		case 0x3E:
			printf("MVI A, 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0x3F: printf("CMC\n"); break;
		case 0x40: printf("MOV B, B\n"); break;
		case 0x41: printf("MOV B, C\n"); break;
		case 0x42: printf("MOV B, D\n"); break;
		case 0x43: printf("MOV B, E\n"); break;
		case 0x44: printf("MOV B, H\n"); break;
		case 0x45: printf("MOV B, L\n"); break;
		case 0x46: printf("MOV B, M\n"); break;
		case 0x47: printf("MOV B, A\n"); break;
		case 0x48: printf("MOV C, B\n"); break;
		case 0x49: printf("MOV C, C\n"); break;
		case 0x4A: printf("MOV C, D\n"); break;
		case 0x4B: printf("MOV C, E\n"); break;
		case 0x4C: printf("MOV C, H\n"); break;
		case 0x4D: printf("MOV C, L\n"); break;
		case 0x4E: printf("MOV C, M\n"); break;
		case 0x4F: printf("MOV C, A\n"); break;
		case 0x50: printf("MOV D, B\n"); break;
		case 0x51: printf("MOV D, C\n"); break;
		case 0x52: printf("MOV D, D\n"); break;
		case 0x53: printf("MOV D, E\n"); break;
		case 0x54: printf("MOV D, H\n"); break;
		case 0x55: printf("MOV D, L\n"); break;
		case 0x56: printf("MOV D, M\n"); break;
		case 0x57: printf("MOV D, A\n"); break;
		case 0x58: printf("MOV E, B\n"); break;
		case 0x59: printf("MOV E, C\n"); break;
		case 0x5A: printf("MOV E, D\n"); break;
		case 0x5B: printf("MOV E, E\n"); break;
		case 0x5C: printf("MOV E, H\n"); break;
		case 0x5D: printf("MOV E, L\n"); break;
		case 0x5E: printf("MOV E,  M\n"); break;
		case 0x5F: printf("MOV E, A\n"); break;
		case 0x60: printf("MOVE H, B\n"); break;
		case 0x61: printf("MOVE H, C\n"); break;
		case 0x62: printf("MOVE H, D\n"); break;
		case 0x63: printf("MOVE H, E\n"); break;
		case 0x64: printf("MOVE H, H\n"); break;
		case 0x65: printf("MOVE H, L\n"); break;
		case 0x66: printf("MOVE H, M\n"); break;
		case 0x67: printf("MOVE H, A\n"); break;
		case 0x68: printf("MOVE L, B\n"); break;
		case 0x69: printf("MOVE L, C\n"); break;
		case 0x6A: printf("MOVE L, D\n"); break;
		case 0x6B: printf("MOVE L, E\n"); break;
		case 0x6C: printf("MOVE L, H\n"); break;
		case 0x6D: printf("MOVE L, L\n"); break;
		case 0x6E: printf("MOVE L, M\n"); break;
		case 0x6F: printf("MOVE L, A\n"); break;
		case 0x70: printf("MOVE M, B\n"); break;
		case 0x71: printf("MOVE M, C\n"); break;
		case 0x72: printf("MOVE M, D\n"); break;
		case 0x73: printf("MOVE M, E\n"); break;
		case 0x74: printf("MOVE M, H\n"); break;
		case 0x75: printf("MOVE M, L\n"); break;
		case 0x76: printf("HLT\n"); break;
		case 0x77: printf("MOVE M, A\n"); break;
		case 0x78: printf("MOVE A, B\n"); break;
		case 0x79: printf("MOVE A, C\n"); break;
		case 0x7A: printf("MOVE A, D\n"); break;
		case 0x7B: printf("MOVE A, E\n"); break;
		case 0x7C: printf("MOVE A, H\n"); break;
		case 0x7D: printf("MOVE A, L\n"); break;
		case 0x7E: printf("MOVE A, M\n"); break;
		case 0x7F: printf("MOVE A, A\n"); break;
		case 0x80: printf("ADD B\n"); break;
		case 0x81: printf("ADD C\n"); break;
		case 0x82: printf("ADD D\n"); break;
		case 0x83: printf("ADD E\n"); break;
		case 0x84: printf("ADD H\n"); break;
		case 0x85: printf("ADD L\n"); break;
		case 0x86: printf("ADD M\n"); break;
		case 0x87: printf("ADD A\n"); break;
		case 0x88: printf("ADD B\n"); break;
		case 0x89: printf("ADD C\n"); break;
		case 0x8A: printf("ADD D\n"); break;
		case 0x8B: printf("ADD E\n"); break;
		case 0x8C: printf("ADD H\n"); break;
		case 0x8D: printf("ADD L\n"); break;
		case 0x8E: printf("ADD M\n"); break;
		case 0x8F: printf("ADD A\n"); break;
		case 0x90: printf("SUB B\n"); break;
		case 0x91: printf("SUB C\n"); break;
		case 0x92: printf("SUB D\n"); break;
		case 0x93: printf("SUB E\n"); break;
		case 0x94: printf("SUB H\n"); break;
		case 0x95: printf("SUB L\n"); break;
		case 0x96: printf("SUB M\n"); break;
		case 0x97: printf("SUB A\n"); break;
		case 0x98: printf("SBB B\n"); break;
		case 0x99: printf("SBB C\n"); break;
		case 0x9A: printf("SBB D\n"); break;
		case 0x9B: printf("SBB E\n"); break;
		case 0x9C: printf("SBB H\n"); break;
		case 0x9D: printf("SBB L\n"); break;
		case 0x9E: printf("SBB M\n"); break;
		case 0x9F: printf("SBB A\n"); break;
		case 0xA0: printf("ANA B\n"); break;
		case 0xA1: printf("ANA C\n"); break;
		case 0xA2: printf("ANA D\n"); break;
		case 0xA3: printf("ANA E\n"); break;
		case 0xA4: printf("ANA H\n"); break;
		case 0xA5: printf("ANA L\n"); break;
		case 0xA6: printf("ANA M\n"); break;
		case 0xA7: printf("ANA A\n"); break;
		case 0xA8: printf("XRA B\n"); break;
		case 0xA9: printf("XRA C\n"); break;
		case 0xAA: printf("XRA D\n"); break;
		case 0xAB: printf("XRA E\n"); break;
		case 0xAC: printf("XRA H\n"); break;
		case 0xAD: printf("XRA L\n"); break;
		case 0xAE: printf("XRA M\n"); break;
		case 0xAF: printf("XRA A\n"); break;
		case 0xB0: printf("ORA B\n"); break;
		case 0xB1: printf("ORA C\n"); break;
		case 0xB2: printf("ORA D\n"); break;
		case 0xB3: printf("ORA E\n"); break;
		case 0xB4: printf("ORA H\n"); break;
		case 0xB5: printf("ORA L\n"); break;
		case 0xB6: printf("ORA M\n"); break;
		case 0xB7: printf("ORA A\n"); break;
		case 0xB8: printf("CMP B\n"); break;
		case 0xB9: printf("CMP C\n"); break;
		case 0xBA: printf("CMP D\n"); break;
		case 0xBB: printf("CMP E\n"); break;
		case 0xBC: printf("CMP H\n"); break;
		case 0xBD: printf("CMP L\n"); break;
		case 0xBE: printf("CMP M\n"); break;
		case 0xBF: printf("CMP A\n"); break;
		case 0xC0: printf("RNZ\n"); break;
		case 0xC1: printf("POP B\n"); break;
		case 0xC2: 
			printf("JNZ 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xC3:
			printf("JMP 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xC4:
			printf("CNZ 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xC5: printf("PUSH B\n"); break;
		case 0xC6:
			printf("ADI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xC7: printf("RST 0\n"); break;
		case 0xC8: printf("RZ\n"); break;
		case 0xC9: printf("RET\n"); break;
		case 0xCA:
			printf("JZ 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xCB:
			printf("*JMP 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xCC:
			printf("CZ 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xCD:
			printf("CALL 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xCE:
			printf("ACI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xCF: printf("RST 1\n"); break;
		case 0xD0: printf("RNC\n"); break;
		case 0xD1: printf("POP D\n"); break;
		case 0xD2:
			printf("JNC 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xD3:
			printf("OUT 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xD4:
			printf("CNC 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xD5: printf("PUSH D\n"); break;
		case 0xD6: 
			printf("SUI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xD7: printf("RST 2\n"); break;
		case 0xD8: printf("RC\n"); break;
		case 0xD9: printf("*RET\n"); break;
		case 0xDA:
			printf("JC 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xDB:
			printf("IN 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xDC:
			printf("CC 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xDD:
			printf("*CALL 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xDE:
			printf("SBI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xDF: printf("RST 3\n"); break;
		case 0xE0: printf("RP\n"); break;
		case 0xE1: printf("POP PSW\n"); break;
		case 0xE2:
			printf("JPO 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xE3: printf("XTHL\n"); break;
		case 0xE4:
			printf("CPO 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xE5: printf("PUSH H\n"); break;
		case 0xE6:
			printf("ANI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xE7: printf("RST 4\n"); break;
		case 0xE8: printf("RPE\n"); break;
		case 0xE9: printf("PCHL\n"); break;
		case 0xEA:
			printf("JPE 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xEB: printf("XCHG\n"); break;
		case 0xEC:
			printf("CPE 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xED:
			printf("*CALL 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xEE:
			printf("XRI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xEF: printf("RST 5\n"); break;
		case 0xF0: printf("RP\n"); break;
		case 0xF1: printf("POP PSW\n"); break;
		case 0xF2:
			printf("JP 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xF3: printf("DI\n"); break;
		case 0xF4:
			printf("CP 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xF5: printf("PUSH PSW\n"); break;
		case 0xF6:
			printf("ORI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xF7: printf("RST 6\n"); break;
		case 0xF8: printf("RM\n"); break;
		case 0xF9: printf("SPHL\n"); break;
		case 0xFA:
			printf("JM 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xFB: printf("EI\n"); break;
		case 0xFC:
			printf("CM 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xFD:
			printf("*CALL 0x%02x%02x\n", opcode2, opcode1);
			optBytes = 3;
			break;
		case 0xFE:
			printf("CPI 0x%02x\n", opcode1);
			optBytes = 2;
			break;
		case 0xFF: printf("RST 7\n"); break;
		
		
		
		
	}
	return optBytes;
}
