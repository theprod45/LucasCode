#include"chip8.h"
#include<iostream>
#include<chrono>

int main(){
		char const* romFilename = "IBM.ch8";
		Chip8 Computer;
		Computer.loadRom(romFilename);
		
		Computer.cycle();
		while(true){
			//system("clear");
			Computer.cycle();
			//Computer.draw();
		}
}
