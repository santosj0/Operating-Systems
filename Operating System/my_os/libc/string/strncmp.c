#include "../include/string.h"

int strncmp(const char* s1, const char* s2, size_t n)
{
	//For now, the function works, but there are no safeguards
	//towards larger n values compared to strings
	
	//Compare based on the alloted size
	for(n;n>0;n--)
		
		//If both strings return a null character, then they are
		//equal to one another. If not and one of them do have a null
		//character, then return the opposite representation to show that
		//the one who returned a null character first is small since it could
		//not continue with the comparison
		if(*s1=='\0' && *s2=='\0'){
			return 0;
		}
		else if(*s1=='\0'){
			return -1;
		}
		else if(*s2=='\0'){
			return 1;
		}
		//If neither string has a null character, then continue with the comparison
		//If the difference between s1 - s2 does not
		//equal 0, than return the difference.
		else if(*s1 - *s2 != 0){
			return *s1-*s2;
		}
		//If they do equal 0, than increase pointers to
		//both 
		else{
			s1++,s2++;
		}
	//If for loop finishes, that means the two strings
	//based on the desired length were equal to one another,
	//thus returning a 0
	return 0;
}