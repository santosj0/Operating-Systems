#include "../include/string.h"

char* strncat(char* dest, const char* src, size_t n)
{
    //Return the original address of dest
    char* ret = dest;
	
	//Move the memory address pointer the amount of times
	//to specified by temp
	while(*dest != '\0'){
		dest++;
	}
	
	//Replace the contents of dest at that memory address
	//with the contents of src and then increment the pointer
	//to the next memory address.
	for(n;n>0;n--){
	    
		if(*src == '\0'){
		    *dest=*src;
	        return ret;
		}else{
		    *dest=*src;
		    dest++,src++;
		}
	}
	//Move the memory address pointer up by one and then
	//add in the null value.
	dest++;
	*dest='\0';
	
	//Return the new concat word;
	return ret;
}