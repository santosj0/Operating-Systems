#include "../include/string.h"

char* strstr(char* s1, const char* s2)
{
	//If the length of the second string is
	//greater than the length of the first string
	//then it means that the second string is not
	//inside the first string, thus, return a 0.
	if(strlen(s2) > strlen(s1)){
		return 0;
	}
	
	size_t c1 = strlen(s1);   //Used to iterate through the string
	size_t c2 = strlen(s2);   //Used as total length for comparison
	int x = 0;				  //Used to store memcmp value
	
	//Loop to iterate through s1
	for(c1;c1>0;c1--){
		
		//Grabs the value of the comparing strings
		x = memcmp(s1,s2,c2);
	
		//If the value from memcmp is 0, then that means
		//from the current s1 location to the end of the
		//second strings left is true, if not, move the
		//pointer to the next memory address in s1.
		if(x==0){
			return s1;
		}
		else{
			s1++;
		}		
	}
	return 0;
	
}