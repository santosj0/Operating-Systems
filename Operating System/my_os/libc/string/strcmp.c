#include "../include/string.h"

int strcmp(const char* s1, const char* s2)
{	
	//If the length of s1 is greater than the length of
	//s2, then return 1. If its the opposite, return -1.
	//If they are the same length, then do the comparison.
	if(strlen(s1) > strlen(s2)){
		return 1;
	}
	else if(strlen(s1) < strlen(s2)){
		return -1;
	}
	else{
		
		//Create a while loop to iterate through the character
		//array until the null character appears.
		while(*s1 != '\0'){
			
			//If the difference between s1 - s2 does not
			//equal 0, than return the difference.
			if(*s1 - *s2 != 0){
				return *s1-*s2;
			}
			//If they do equal 0, than increase the counter and
			//continue
			else{
				s1++,s2++;
			}
		}	
		//If there is no difference between any characters in both
		//arrays, then return 0 saying that they are equal.
		return 0;
	}
}