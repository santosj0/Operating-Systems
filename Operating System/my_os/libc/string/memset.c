#include "../include/string.h"

void* memset(void* bufptr, int value, size_t size)
{	
	//Sets the buffer to be unsigned meaning that
	//the ASCII table goes from 0 to 255 instead of
	//-128 to 128
	unsigned char* b=bufptr;
	
	//Create a for loop where the memory address of b
	//is first replaced with the unsigned character of
	//the value(i.e. the ASCII number to represent the 
	//character) before moving the memory address to the 
	//next location where it repeats until size is equal 
	//to 0.
	for(size;size!=0;size--){
		*b = (unsigned char)value;
		b++;
	}
	//Once the loop finishes, it returns the new string
	return bufptr;
}