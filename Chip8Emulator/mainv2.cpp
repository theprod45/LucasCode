#include "Chip8.h"
#include<iostream>
#include<chrono>


int main(){
		Chip8 Computer;
		Computer.load();
		Computer.cycle();
		int cycleDelay = 1;
		auto lastCycleTime = std::chrono::high_resolution_clock::now();

		
		
		int i = 512; // 512 DEC
		while(i < 4096){
			auto currentTime = std::chrono::high_resolution_clock::now();
			float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
			if (dt > cycleDelay)
			{
			lastCycleTime = currentTime;

			Computer.cycle();
			Computer.draw();
			i++;
			//system("clear");
			printf("\033c");
			}
		}
		//Computer.draw();
}
