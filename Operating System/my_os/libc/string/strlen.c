#include "../include/string.h"

size_t strlen(const char* str)
{
	//Creates an unsigned integer variable
	//of 0
	size_t ret = 0;
	
	//Creates a while loop that will go to each
	//character in the string looking for a null
	//character which is represented by \0. If
	//the null character is not found, then it will
	//increase ret to check the next character in the
	//character array essentially providing the number
	//of times ret was looped, i.e. the string's length
	while(str[ret] != 0)
		ret++;
	return ret;
}