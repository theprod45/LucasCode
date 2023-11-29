#include <iostream>
#include <string>
#include <math.h>
using namespace std;

string binToInt(string b){
	if(b.length() != 16){
		return "Must Enter 16-bit Binary Integer";
	}
	// Converts Binary String to Base10 String
	int sum = 0;
	// If bit is occupied in string add 2^i to sum
	for(int i = 0; i < 16; i++){
		if(b[i] == '1'){
			sum += pow(2,15-i);
		}
	}
	return(to_string(sum));
}


string intToHex(string i){
	// Converts Base 10 to Hex String
	if(i == "0"){ return("0");} // If entered 0 
	string result = "";
	int temp = stoi(i);
	while(temp != 0){
		if( (temp % 16) >= 10){
			if(temp % 16 == 10)
				result.insert(0,"A");
			else if(temp % 16 == 11)
				result.insert(0,"B");
			else if(temp % 16 == 12)
				result.insert(0,"C");
			else if(temp % 16== 13)
				result.insert(0,"D");
			else if(temp % 16 == 14)
				result.insert(0,"E");
			else if(temp % 16 == 15)
				result.insert(0,"F");
		}
		else{
			result.insert(0,to_string(temp%16));
		}
		temp = temp/16;
	}
	return result;
}

string addHex(string h1, string h2){
	// Adds two hex and returns string of the anwser
	int i1 = stoi(h1,0,16);
	int i2 = stoi(h2,0,16);
	int sum = i1 + i2;
	return(intToHex(to_string(sum)));
}

// Doesn't Work, I got 2's compliment to work but when I add doesn't give correct result
string subUnsignedInts(string x, string y){
	// Subs two unsigned binary ints 
	// Just like adding to Binary numbers, except taje 2's compliment of number being subtracted by
	// A + (-B)
	
	// First flip all the bits
	for(int i =0 ; i < y.length(); i++){
		// Flipping all the bits
		if(y[i] == '0'){
			y[i] = '1';
		}
		else{
			y[i] = '0';
		}
	}
	// add 1 to prev step
	for(int i = y.length(); i > 0 ;i--){
		if(y[i-1] == '0'){
			y[i-1] = '1';
			break;
		}
		else{
			y[i-1] = '0';
		}
	}
	// Now add x + y 
	string sum = "";
	int temp = 0;
	int xsize = x.size() -1;
	int ysize = y.size() -1;
	while(xsize >= 0 || ysize >=0 || temp == 1){
		temp += ((xsize >= 0)? x[xsize] - '0': 0);
		temp += ((ysize >= 0)? y[ysize] - '0': 0);
		sum = char(temp % 2 + '0') + sum;
		temp /= 2;
		xsize--;
		ysize--;
	}
	
	
	
	return sum;
}

int main(){
	cout << addHex("7FFF", "1") << endl;
}
