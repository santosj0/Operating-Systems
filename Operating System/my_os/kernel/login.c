//Log into the terminal
//Input: Username, Password
//Output: integer true = 0 or false = 1
int login(char user[], char pass[]){
	
	char compare_user[10];
	compare_user[0] = '\0';
	int i;

	//First we check to see if the username is in any of the valid usernames
	for(i=6;i>0;i--){		
		//Conditional to check to make sure that username is in array of usernames
		if(strcmp(v_username[i-1],user) == 0){
			strcat(compare_user,user);
			break;
		}
	}

	//We check if compare_user was updated
	if(compare_user[0] == '\0'){
		return 1;
	}else{
		
		//Now we check if the password was right
		char compare_password[15];
		compare_password[0] = '\0';

		//Loop through v_password
		for(i=6;i>0;i--){
			//Conditional to check to make sure that password is in array of valid passwords
			if(strcmp(v_password[i-1],pass) == 0){
				strcat(compare_password,pass);
				break;
			}
		}

		//We check if compare_password was updated
		if(compare_password[0] == '\0'){
			return 1;
		}else{
			
			//Now we need to make sure the pairs works
			if(strcmp(user,v_username[0]) == 0 && strcmp(pass,v_password[0]) == 0){
				return 0;
			}else if(strcmp(user,v_username[1]) == 0 && strcmp(pass,v_password[1]) == 0){
				return 0;
			}else if(strcmp(user,v_username[2]) == 0 && strcmp(pass,v_password[2]) == 0){
				return 0;
			}else if(strcmp(user,v_username[3]) == 0 && strcmp(pass,v_password[3]) == 0){
				return 0;
			}else if(strcmp(user,v_username[4]) == 0 && strcmp(pass,v_password[4]) == 0){
				return 0;
			}else if(strcmp(user,v_username[5]) == 0 && strcmp(pass,v_password[5]) == 0){
				return 0;
			}else {
				return 1;
			}
			
		}

	}

}
