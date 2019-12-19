#include "../include/string.h"

//Converts string to integer
//Source: https://www.geeksforgeeks.org/write-your-own-atoi/
int atoi(const char* str){
		
		int sign = 1; //Sign first starts as 1
		int ret = 0; //Initialize the result
		int i = 0;	//Counter
		
		if(*str == '-'){
			sign = -1;
			i++;
		}
		
		//Loop through the string until the null value
		for(i; str[i] != '\0'; i++){
				ret = ret * 10 + str[i] - '0';
		}
		
		return sign*ret;
}