#include "../include/string.h"

int memcmp(const void* aptr, const void* bptr, size_t size)
{
	//First, get the memory address of each string
	const unsigned char *aptr1 = aptr, *bptr1 = bptr;
	
	//Create a for loop until size = 0
	for(size;size!=0;size--)
		//If string1 memory address does not equal
		//string2 memory address, then return the
		//difference. Negative means that string2
		//is larger and positive means that string1
		//is larger.
		if( *aptr1 != *bptr1)
			return *aptr1 - *bptr1;
		//Increase the pointer location to compare the
		//memory address of the next character
		else
			aptr1++,bptr1++;
		
	//If none of the memory address are different,
	//return 0 to indicate that they are equal
	return 0;
}