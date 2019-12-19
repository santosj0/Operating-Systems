#include "../include/string.h"

char* strchr(const char *s, int c)
{
	//Create a loop to iterate through the string until the null value
	while(*s != '\0'){
		
		//If the number representation of the character
		//in the first string is the same number representation
		//of the desired character, then return the location of
		//the string. Otherwise, increment the pointer of the
		//memory address
		if(*s == c){
			return s;
		}
		else{
			s++;
		}
	}
	//If none of the number representations match to one another,
	//then return the null value;
	return s;
}
