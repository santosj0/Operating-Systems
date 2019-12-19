#include "../include/string.h"

//Assumes that d is an empty string array
char* parameter2(char* d, const char* s){

	//First we store the initial location of the string pointer
	char* ret = d;
	int i;
	for(i=2;i>0;i--){
		//Now we loop through source and concat until we reach null or white space
		while(*s != 0x20 && *s != '\0'){
			s++;
		}

		//Increment into the next paramter
		s++;
	}

	//Now we loop through source and concat until we reach null or white space
	while(*s != 0x20 && *s != '\0'){
		*d = *s;
		d++, s++;
	}

	//Add a null at end of d to signify that it is a string
	*d = '\0';

	return ret;

}
