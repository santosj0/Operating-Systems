static char* const VGA_MEMORY = (char*) 0xb8000;

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

//Clears the screen and places the little console symbol at the bottom
void go_into_terminal(){
	int clear = 3998;
	while(clear >= 0){
		VGA_MEMORY[clear] = 0x00;
		clear = clear - 2;
	}

	VGA_MEMORY[0] = 0x20;
	VGA_MEMORY[1] = 0x07;
	VGA_MEMORY[2] = 0x26;
	VGA_MEMORY[3] = 0x07;
	VGA_MEMORY[4] = 0x20;
	VGA_MEMORY[5] = 0x07;
	VGA_MEMORY[6] = 0x3E;
	VGA_MEMORY[7] = 0x07;
	VGA_MEMORY[8] = 0x20;
	VGA_MEMORY[9] = 0x07;
	update_cursor(5,0);
}

//Writes the console symbol based on parameters
void write_console(int ystart){

	//Based on which line we are on, I will multiple it by 160
	int location = ystart*160;

	VGA_MEMORY[location] = 0x20;
	VGA_MEMORY[location+1] = 0x07;
	VGA_MEMORY[location+2] = 0x26;
	VGA_MEMORY[location+3] = 0x07;
	VGA_MEMORY[location+4] = 0x20;
	VGA_MEMORY[location+5] = 0x07;
	VGA_MEMORY[location+6] = 0x3E;
	VGA_MEMORY[location+7] = 0x07;
	VGA_MEMORY[location+8] = 0x20;
	VGA_MEMORY[location+9] = 0x07;

	//Now we update the cursor based on the location
	update_cursor(5,ystart);

}

//Clears only the last line
void clear_last_line(){
	int clear = 3998;
	while(clear >= 3680){
		VGA_MEMORY[clear] = 0x00;
		clear = clear - 2;
	}

	VGA_MEMORY[3680] = 0x20;
	VGA_MEMORY[3681] = 0x07;
	VGA_MEMORY[3682] = 0x26;
	VGA_MEMORY[3683] = 0x07;
	VGA_MEMORY[3684] = 0x20;
	VGA_MEMORY[3685] = 0x07;
	VGA_MEMORY[3686] = 0x3E;
	VGA_MEMORY[3687] = 0x07;
	VGA_MEMORY[3688] = 0x20;
	VGA_MEMORY[3689] = 0x07;

	update_cursor(5,23);
}

//Clears the entire screen
void clear_screen(){
	int clear = 3998;
	while(clear >= 0){
		VGA_MEMORY[clear] = 0x00;
		clear = clear - 2;
	}
}

//Add the bottom most line to the bottom buffer
void add_to_bottombuffer(){

	//First check to see if there is a null
	int i;
	for(i=0;i<6;i++){
		if(bottombuffer[i][0] == '\0'){
			break;
		}
	}

	int count = 3520;
	char line1[100];
	line1[0] = '\0';
	while(count < 3680){
		//Take each character from the last line and add it to a string array
		char charstr1[2];
		ctos(charstr1,VGA_MEMORY[count]);
		strcat(line1,charstr1);
		count = count + 2;
	}
	

	//int i will give me a number to use
	if(i==6){

		strcpy(bottombuffer[5],bottombuffer[4]);
		strcpy(bottombuffer[4],bottombuffer[3]);
		strcpy(bottombuffer[3],bottombuffer[2]);
		strcpy(bottombuffer[2],bottombuffer[1]);
		strcpy(bottombuffer[1],bottombuffer[0]);
		strcpy(bottombuffer[0],line1);

	}else if(i==0){

		strcpy(bottombuffer[0],line1);

	}else{
		//In reverse of i, set each element to the next level
		for(i; i>0;i--){
			strcpy(bottombuffer[i],bottombuffer[i-1]);
		}

		strcpy(bottombuffer[0],line1);

	}

}

//Adds the top most line to the up buffer
void add_to_upbuffer(int amount){
	
	//First check to see if there is a null
	int i;
	for(i=0;i<6;i++){
		if(upbuffer[i][0] == '\0'){
			break;
		}
	}

	int count = 0;
	char line1[80];
	line1[0] = '\0';
	while(count < 160){
		//Take each character from the first line and add it to a string array
		char charstr1[2];
		ctos(charstr1,VGA_MEMORY[count]);
		strcat(line1,charstr1);
		count = count + 2;
	}
	
	//Do the same for line two
	count = 160;
	char line2[80];
	line2[0] = '\0';
	while(count < 320){
		char charstr2[2];
		ctos(charstr2,VGA_MEMORY[count]);
		strcat(line2,charstr2);
		count = count + 2;
	}

	//Do the same for line three
	count = 320;
	char line3[80];
	line3[0] = '\0';
	while(count < 480){
		char charstr3[2];
		ctos(charstr3,VGA_MEMORY[count]);
		strcat(line3,charstr3);
		count = count + 2;
	}

	//int i will give me a number to use
	//Condition if all string buffers is taken and we need to add 2 lines
	if(i>3 && amount==3){
		
		strcpy(upbuffer[5],upbuffer[2]);
		strcpy(upbuffer[4],upbuffer[1]);
		strcpy(upbuffer[3],upbuffer[0]);
		strcpy(upbuffer[2],line1);
		strcpy(upbuffer[1],line2);
		strcpy(upbuffer[0],line3);

	}else if(i>4 && amount==2){

		//Now we need to move the spots to their respective places
		strcpy(upbuffer[5],upbuffer[3]);
		strcpy(upbuffer[4],upbuffer[2]);
		strcpy(upbuffer[3],upbuffer[1]);
		strcpy(upbuffer[2],upbuffer[0]);
		strcpy(upbuffer[1],line1);
		strcpy(upbuffer[0],line2);

	}
	else if(i==6){

		strcpy(upbuffer[5],upbuffer[4]);
		strcpy(upbuffer[4],upbuffer[3]);
		strcpy(upbuffer[3],upbuffer[2]);
		strcpy(upbuffer[2],upbuffer[1]);
		strcpy(upbuffer[1],upbuffer[0]);
		strcpy(upbuffer[0],line1);

	}
	//Condition if no string buffers is taken
	else if(i==0 && amount==3){
		strcpy(upbuffer[2],line1);
		strcpy(upbuffer[1],line2);
		strcpy(upbuffer[0],line3);
	}
	else if(i==0 && amount==2){

		strcpy(upbuffer[1],line1);
		strcpy(upbuffer[0],line2);
	
	}
	else if(i==0){

		strcpy(upbuffer[0],line1);

	}
	//Condition if only a certain amount of buffers is taken
	else if(amount==3){
		int k = i;
		int p = i;
		
		for(i; i>0;i--){
			strcpy(upbuffer[i],upbuffer[i-1]);
		}

		for(k;k>0;k--){
			strcpy(upbuffer[k],upbuffer[k-1]);
		}

		for(p;p>0;p--){
			strcpy(upbuffer[p],upbuffer[p-1]);
		}
		
		strcpy(upbuffer[2],line1);
		strcpy(upbuffer[1],line2);
		strcpy(upbuffer[0],line3);
		

	}
	else if(amount==2){
		int k = i;	

		for(i; i>0;i--){
			strcpy(upbuffer[i],upbuffer[i-1]);
		}

		for(k;k>0;k--){
			strcpy(upbuffer[k],upbuffer[k-1]);
		}

		strcpy(upbuffer[1],line1);
		strcpy(upbuffer[0],line2);


	}
	else{

		//In reverse of i, set each element to the next level
		for(i; i>0;i--){
			strcpy(upbuffer[i],upbuffer[i-1]);
		}

		strcpy(upbuffer[0],line1);

	}

}

//Shifts the entire screen down
void shift_down(int value){
	
	for(value;value>0;value--){

		int count1 = 3519;
		int count2 = 3679;

		//First, create a loop until count1 is less than 0
		while(count1 > 0){

			int temp = count2;
			//Now we loop to replace the lines
			while(count2 > (temp - 160)){
				VGA_MEMORY[count2] = VGA_MEMORY[count1];
				count1--,count2--;
			}

			/*
			//Now we decrement both
			count1 = count1 - 160;
			count2 = count2 - 160;
			*/
		}
	
	}

}

//Shifts the entire screen up
void shift_up(int value){

	for(value;value>0;value--){

		int count1 = 0;
		int count2 = 160;
		while(count2 < 3999){
			VGA_MEMORY[count1] = VGA_MEMORY[count2];
			count1++, count2++;
		}

	}

}

//Partial shift_up
void partial_up(){

	int count1 = 0;
	int count2 = 160;
	while(count2<3678){
		VGA_MEMORY[count1] = VGA_MEMORY[count2];
		count1++, count2++;
	}

}

//Removes the first string from bottombuffer and writes it on the screen
void write_bottom_line(){
	
	//First we write the bottom line from bottombuffer[0]
	int i = 0;
	int j = 3520;
	while(bottombuffer[0][i] != '\0'){
		VGA_MEMORY[j] = bottombuffer[0][i];
		VGA_MEMORY[j+1] = 0x07;
		i++;
		j = j + 2;
	}

	//Now we clear the rest of the line
	while(j<3680){
		VGA_MEMORY[j] = 0;
		j++;
	}

	//Now we grab the number of bottom buffer
	for(i=0;i<6;i++){
		if(bottombuffer[i][0] == '\0'){
			break;
		}
	}

	if(i==1){
		bottombuffer[0][0] ='\0';
	}else{
		j = 0;
		i = i - 1;
		for(i;i>0;i--){
			strcpy(bottombuffer[j],bottombuffer[j+1]);
			j++;
		}

		bottombuffer[j][0] = '\0';
	}

}

//Removes the first string from the upbuffer and writes it on the screen
void write_top_line(){

	//First we write the top line from upbuffer[0]
	int i = 0;
	int j = 0;
	while(upbuffer[0][i] != '\0'){
		VGA_MEMORY[j] = upbuffer[0][i];
		VGA_MEMORY[j+1] = 0x07;
		i++;
		j = j + 2;
	}

	//Now we clear the rest of the top line
	while(j<160){
		VGA_MEMORY[j] = 0;
		j++;
	}
		
	//Now we need to shift everything down
	//Gives me where the null value is	
	for(i=0;i<6;i++){
		if(upbuffer[i][0] == '\0'){
			break;
		}
	}
	
	if(i==1){
		upbuffer[0][0] = '\0';
	}else if(i==6){
		strcpy(upbuffer[0],upbuffer[1]);
		strcpy(upbuffer[1],upbuffer[2]);
		strcpy(upbuffer[2],upbuffer[3]);
		strcpy(upbuffer[3],upbuffer[4]);
		strcpy(upbuffer[4],upbuffer[5]);
		upbuffer[5][0] = '\0';
	}else{
		j = 0;
		i = i - 1;
		for(i;i>0;i--){
			strcpy(upbuffer[j],upbuffer[j+1]);
			j++;
		}

		upbuffer[j][0] = '\0';
	}

}

//Clears the upbuffer/bottombuffer
void clear_upbuffer(){

	int i;

	for(i=0;i<6;i++){
		if(upbuffer[i][0] == '\0'){
			break;
		}
	}

	for(;i>0;i--){
		upbuffer[i-1][0] = '\0';
	}

}

void clear_bottombuffer(){

	int i;

	for(i=0;i<6;i++){
		if(bottombuffer[i][0] == '\0'){
			break;
		}
	}

	for(;i>0;i--){
		bottombuffer[i-1][0] = '\0';
	}

}
