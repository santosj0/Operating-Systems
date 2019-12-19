#include "../include/string.h"

char* strcat(char* d, const char* s)
{	
    //First we store the initial location of the string pointer
    char* ret = d;
    
	//Create a while loop where it checks to
	//see if the ASCII code of 0(the null character)
	//appears in the string d. If it doesn't, then it
	//moves onto the next memory address. If it does,
	//then it stops the loop.
	while(*d != '\0'){
		d++;
	}
	//Once d* reaches the null character, start a second
	//while loop where it will start to add in the characters
	//from the string s.
	while(*s != '\0'){
		*d=*s;
		d++,s++;
	}
	//Once s* reaches the null character, simply add it at the
	//end of d* and then return d;
	*d='\0';
	
	return ret;
}