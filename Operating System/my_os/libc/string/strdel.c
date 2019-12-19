#include "../include/string.h"

//Removes a single character from a string
char* strdel(char* dest){
	
	char* ret = dest;
	
	//First we move the dest pointer til null
	while(*dest != '\0'){
		dest++;
	}
	
	//Next, we move the point back by one
	dest--;
	//Then place a null value at that position
	*dest = '\0';
	
	return ret;
	
}