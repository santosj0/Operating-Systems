//This function parses the string with the different parameters
//Input: String with space as a delimitor
//Output: Integer - 1 being success, 0 being failure

int run_command(char com[]){

	//First, we run through the command only to get the first part
	char part1[200];
	strparse(part1,com);

	char* list_of_commands[] = {"exit","clearscreen", "logout","adduser","deleteuser","showusers"};

	if(strcmp(list_of_commands[0],part1) == 0){

		//First we exit out of the console and then the terminal		
		exit = 2;
		terminal_loop = 2;

		//Now we print a thank you message
		clear_screen();
		
		char* str = "Thank you very much for using my console! :D";
		int i = 0;
		int j = (11*160)+30;		
		while (str[i] != '\0') {
			VGA_MEMORY[j] = str[i];
			VGA_MEMORY[j+1] = 0x07;
			i++;
			j = j + 2;
		}
	
		return 1;

	}else if(strcmp(list_of_commands[1],part1) == 0){

		go_into_terminal();
		xpos = 5, ypos = 0;
		clear_bottombuffer();
		clear_upbuffer();
		update_cursor(xpos,ypos);
		return 2;

	}else if(strcmp(list_of_commands[2],part1) == 0){

		exit = 2;
		clear_screen();
		return 3;

	}else if(strcmp(list_of_commands[3],part1) == 0){

		//First we check to make sure that a spot is available
		int i;
		for(i=0;i<6;i++){
			if(v_username[i][0] == '\0'){
				break;
			}
		}

		if(i==6){
			return 0;
		}else{
			//We need to get the username parameter and password parameter
			char uname[200], pword[200];
			uname[0] = '\0';
			pword[0] = '\0';
			parameter1(uname,com);
			parameter2(pword,com);

			if(*uname==0 || *pword==0){
			    return 0;
			}else{
			    
				int len = strlen(uname);
				int len1 = strlen(pword);
				if(len >= 20 || len1 >= 20){
					return 0;
				}else{
                			strcpy(v_username[i],uname);
					strcpy(v_password[i],pword);
					return 4;
				}
			}
		}

	}else if(strcmp(list_of_commands[4],part1) == 0){
	
		//Delete user
		//First check to make sure they do not delete last user
		//Check to make sure that they have username/password parameters
		//Then check to make sure username/password match
		//Then remove user from list
		return 0;
	
	}else if(strcmp(list_of_commands[5],part1) == 0){
	
		//Show users
		//Use up arrow as an example of shifting up minus the write line
		//print to last line checking to make sure that each username can fit on the line
		//If username cannot fit on the line, shift up and then continue on
		//Add about.... 4 or 5 spaces inbetween each username for displaying purposes
		return 0;
	
	}else{
		return 0;
	}

	

}

//Prints an error message
void print_error(int yposition){
	
	char* str = " & > Please input a correct command";
	int i = 0;
	int j = (yposition*160);		
	while (str[i] != '\0') {
		VGA_MEMORY[j] = str[i];
		VGA_MEMORY[j+1] = 0x07;
		i++;
		j = j + 2;
	}

}

//Prints user created message
void print_user_created(int yposition){
	
	char* str = " & > User has been successfully created";
	int i = 0;
	int j = (yposition*160);		
	while (str[i] != '\0') {
		VGA_MEMORY[j] = str[i];
		VGA_MEMORY[j+1] = 0x07;
		i++;
		j = j + 2;
	}

}
