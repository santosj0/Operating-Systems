#include "../include/string.h"

char* strcpy(char* d, const char* s)
{
	//Create a while loop where the character
	//in the s memory address replaces the
	//character in the d memory address
	while(*s != '\0'){
		*d = *s;
		d++,s++;
	}
	//Include the null character at the end and then
	//return d
	*d = '\0';
	
	return d;
}