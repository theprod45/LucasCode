#include "Chip8.h"
#include<iostream>

int main(){
		Chip8 Computer;
		Computer.load();
		Computer.cycle();
		
		int i = 512; // 512 DEC
		while(i < 4095){
			Computer.cycle();
			//Computer.draw();
			i++;
			//system("clear");
		}
		Computer.draw();
}
