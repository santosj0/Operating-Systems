#include "stdint.h"

//Global Variable Section
char v_username[6][20] = {"admin","invader zim"};
char v_password[6][20] = {"pass","zoboomafoo"};
char upbuffer[6][85];
char bottombuffer[6][85];
int xpos, ypos;
int terminal_loop, login_loop, exit;

#include "libc/include/string.h"
#include "kernel/port.c"
#include "kernel/video.c"
#include "kernel/keyboard.c"
#include "kernel/login.c"
#include "kernel/commands.c"

// Driver
int main(void) {

	//Create an Overall loop
	terminal_loop = 1;
	while(terminal_loop == 1){
	
		//First we ask the user for their username by printing the string into the buffer
		const char* str = "Please enter a username:";
		unsigned int i = 0;
		unsigned int j = 0;		
		while (str[i] != '\0') {
			VGA_MEMORY[j] = str[i];
			VGA_MEMORY[j+1] = 0x07;
			i++;
			j = j + 2;
		}
	
		//Create a loop for login
		login_loop = 1;
		while(login_loop == 1){		
		
			//Next we enable the cursor and move it to the next line
			//Also move the VGA point to the next line
			xpos=0,ypos=1;
			enable_cursor(11,12);
			update_cursor(xpos,ypos);
			unsigned int location = xpos + (ypos*160);
		
			//Initialize a username string
			char username[50];
			username[0] = '\0';	
	
			//Now we need to wait for a button press
			//Just in case, we have a way to exit out of the infinite loop
			exit = 1;
			while(exit == 1){
				uint8_t byte;
				while(byte = scan()){
		
					//If the hex from the scancode is a valid key
					if(check_key(byte) == 1){
		
						//Limits the length of the string to 25
						if(location == ((ypos*160)+50)){
							outb(0x60,0);
							break;
						} else{
							//Grab the button and place it in VGA_MEMORY
							//Update the VGA location, update the cursor position
							//Clear out the scancode port
							//Store byte in string array					
							VGA_MEMORY[location] = convert(byte);
							VGA_MEMORY[location+1] = 0x07;
							location = location + 2;
							update_cursor(++xpos,ypos);
							
							//Create a string out of the character
							char charstr[2];
							ctos(charstr,convert(byte));
			
							//Concat that string with username
							strcat(username,charstr);
	
							outb(0x60,0);
							break;
						}
					}
		
					//If the hex from the scancode is the enter key
					else if(byte == 0x1C){
						
						//Exit out of username loop and move onto password loop
						outb(0x60,0);
						exit=2;
						break;
						
					}
		
					//Checks if the scancode is the backspace key
					else if(byte == 0x0E){
						
						//Checks to make sure that backspace does not go past original location
						if(location == ((ypos*160))){
							outb(0x60,0);
							break;
						}else{
							update_cursor(--xpos,ypos);
							location = location - 2;
							VGA_MEMORY[location] = 0x00;
							strdel(username);
							outb(0x60,0);
							break;
						}		
					}
		
				}
		
			}
		
			//Update coordinates/cursor/print password line
			xpos = 0, ypos = 2;
			i = 0;
			j = xpos + (ypos*160);
			str = "Please enter a password: ";
			while (str[i] != '\0') {
				VGA_MEMORY[j] = str[i];
				VGA_MEMORY[j+1] = 0x07;
				i++;
				j = j + 2;
			}
			ypos = 3;
			update_cursor(xpos,ypos);
			location = xpos + (ypos*160);
		
			//Now we do the same thing as before, but this time, with a password
			//Initialize a username string
			char password[50];
			password[0] = '\0';	
		
			//Now we need to wait for a button press
			//Just in case, we have a way to exit out of the infinite loop
			exit = 1;
			while(exit == 1){
				uint8_t byte;
				while(byte = scan()){
		
					//If the hex from the scancode is a valid key
					if(check_key(byte) == 1){
		
						//Limits the length of the string to 25
						if(location == ((ypos*160)+50)){
							outb(0x60,0);
							break;
						} else{
							//Grab the button and place it in VGA_MEMORY
							//Update the VGA location, update the cursor position
							//Clear out the scancode port
							//Store byte in string array					
							VGA_MEMORY[location] = convert(byte);
							VGA_MEMORY[location+1] = 0x07;
							location = location + 2;
							update_cursor(++xpos,ypos);
							
							//Create a string out of the character
							char charstr[2];
							ctos(charstr,convert(byte));
		
							//Concat that string with password
							strcat(password,charstr);
		
							outb(0x60,0);
							break;
						}
					}
		
					//If the hex from the scancode is the enter key
					else if(byte == 0x1C){
						
						outb(0x60,0);
	
						//We check what is returned from login function
						if(login(username,password) == 0){
							//User successfully logged in so break out of login loop
							login_loop = 2;
							exit = 2;
							break;
						}else{
							//User failed to login
							//Clear the screen
							clear_screen();
							
							//Print new message
							i = 0;
							j = 0;
							str = "Username/Password not correct. Please enter a Username: ";
							while (str[i] != '\0') {
								VGA_MEMORY[j] = str[i];
								VGA_MEMORY[j+1] = 0x07;
								i++;
								j = j + 2;
							}
	
							//Exit out of password loop
							exit = 2;
							break;
						}
						
					}
		
					//Checks if the scancode is the backspace key
					else if(byte == 0x0E){
					
						//Checks to make sure that backspace does not go past original location
						if(location == (ypos*160)){
							outb(0x60,0);
							break;
						}else{
							update_cursor(--xpos,ypos);
							location = location - 2;
							VGA_MEMORY[location] = 0x00;
							strdel(password);
							outb(0x60,0);
							break;
						}		
					}
	
				}
	
			}
	
		}
	
		go_into_terminal();
	
		//Now we start with the command section
		xpos = 5, ypos = 0;
		exit = 1;
		int location = 10 + (ypos*160);
		char command[200];
		command[0] = '\0';
		update_cursor(xpos,ypos);
	
		while(exit == 1){
			uint8_t byte;
			while(byte = scan()){
	
				//If the hex from the scancode is a valid key
				if(check_key(byte) == 1){
	
					//Limits the length of the string to 
					if(location == ((ypos*160)+200)){
						outb(0x60,0);
						break;
					} else{
						//Grab the button and place it in VGA_MEMORY
						//Update the VGA location, update the cursor position
						//Clear out the scancode port
						//Store byte in string array					
						VGA_MEMORY[location] = convert(byte);
						VGA_MEMORY[location+1] = 0x07;
						location = location + 2;
						update_cursor(++xpos,ypos);
						
						//Create a string out of the character
						char charstr[2];
						ctos(charstr,convert(byte));
	
						//Concat that string with command
						strcat(command,charstr);
	
						outb(0x60,0);
						break;
					}
				}
	
				//If the hex from the scancode is the enter key
				else if(byte == 0x1C){
					outb(0x60,0);
					
					//Clear the bottom buffer
					clear_bottombuffer();
					
					//We leave the previous line and move onto the next line
					//First update the location based on xpos
					if(xpos > 80){
						ypos = ypos + 2;
					}else {				
						ypos = ypos + 1;
					}
	
					//Now we pass in the command
					int result = run_command(command);
	
					if(result == 0 && ypos < 23){
	
						//Command failed, so run bad line
						print_error(ypos);
	
						ypos++;
						write_console(ypos);
	
					}else if(result == 1){
						
						update_cursor(300,300);	
	
					}else if(result == 4){

						print_user_created(ypos);
						ypos++;
						write_console(ypos);

					}else if(ypos >= 23 && xpos > 80 && result == 0){
						add_to_upbuffer(3);
						shift_up(3);					
						clear_last_line();
						ypos = 23;
						print_error(ypos-1);
					}else if(ypos >= 23 && result == 0){
						add_to_upbuffer(2);
						shift_up(2);
						clear_last_line();
						ypos = 23;
						print_error(ypos-1);
					}

					location = (ypos*160) + 10;
					xpos = 5;
					command[0] = '\0';
	
					break;
					
				}
	
				//Checks if the scancode is the backspace key
				else if(byte == 0x0E){
					
					//Checks to make sure that backspace does not go past original location
					if(location == (10+(ypos*160))){
						outb(0x60,0);
						break;
					}else{
						update_cursor(--xpos,ypos);
						location = location - 2;
						VGA_MEMORY[location] = 0x00;
						strdel(command);
						outb(0x60,0);
						break;
					}		
				}
	
				//Checks if the scancode is the up arrow
				else if(byte == 0x48){
	
					outb(0x60,0);
					//Check to make sure that upbuffer has something
					for(i=0;i<6;i++){
						if(upbuffer[i][0] == '\0'){
							break;
						}
					}
	
					if(i == 0){
						break;
					}else{
	
	
						//Now we need to add whats in the last line to the down buffer
						add_to_bottombuffer();
						//Now we shift everything down
						shift_down(1);
						//Now we take the first line in the upbuffer and fill it
						write_top_line();
	
						break;
	
					}
	
				}
	
				//Checks if the scancode is the down arrow
				else if(byte == 0x50){
	
					outb(0x60,0);
	
					//Check to make sure bottom buffer has something
					for(i=0;i<6;i++){
						if(bottombuffer[i][0] == '\0'){
							break;
						}
					}
	
					if(i==0){
						break;
					}else{
						//First we add top line to upbuffer
						add_to_upbuffer(1);
						//Next we shift everything up
						partial_up();
						//Now we take the first line in the bottombuffer and fill it
						write_bottom_line();
	
						break;
					}
				}

			}

		}
	
	}

	return 0;
}
