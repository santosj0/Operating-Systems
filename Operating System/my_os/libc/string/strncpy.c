#include "../include/string.h"

char* strncpy(char* dest, const char* src, size_t n)
{
	//Create a loop for the amount of times n is used
	//where the character in the memory address of source
	//is copied to the memory address of destination and
	//then increment the pointer by one to preform this on
	//the next memory address.
	for(n;n>0;n--){
		//Create a conditional where if src is equal to null
		//then it breaks out of the loop.
		if(*src=='\0'){
			break;
		}
		else{
			*dest=*src;
			dest++,src++;
		}
	}
	//Once the desired amount of characters has been copied,
	//have to place a null character at the end of dest
	*dest = '\0';
	
	return dest;
	
}