#include "../include/string.h"

char* ctos(char s[2], const char c)
{
	//First put the first character into index 0
	//of the character array
	s[0] = c;
	//Then we place the null character into the second
	//index in the character array
	s[1] = '\0';
	
	//Now we return the location of s;
	return s;
	
}