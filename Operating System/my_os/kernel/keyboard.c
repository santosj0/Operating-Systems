//Returns whatever is inside of port 0x60
//i.e. Keyboard scancode hex
uint8_t scan(void)
{
    uint8_t inkey = inb(0x60);
    return inkey;
}

//Converts the Scancode hex to ASCII hex
uint8_t convert(uint8_t hex){
	
	//a
	if(hex == 0x1E){
		return 0x61;
	}
	//b	
	else if(hex == 0x30){
		return 0x62;
	}
	//c	
	else if(hex == 0x2E){
		return 0x63;
	}
	//d	
	else if(hex == 0x20){
		return 0x64;
	}
	//e	
	else if(hex == 0x12){
		return 0x65;
	}
	//f	
	else if(hex == 0x21){
		return 0x66;
	}
	//g	
	else if(hex == 0x22){
		return 0x67;
	}
	//h
	else if(hex == 0x23){
		return 0x68;
	}
	//i	
	else if(hex == 0x17){
		return 0x69;
	}
	//j
	else if(hex == 0x24){
		return 0x6A;
	}
	//k
	else if(hex == 0x25){
		return 0x6B;
	}
	//l
	else if(hex == 0x26){
		return 0x6C;
	}
	//m	
	else if(hex == 0x32){
		return 0x6D;
	}
	//n	
	else if(hex == 0x31){
		return 0x6E;
	}
	//o
	else if(hex == 0x18){
		return 0x6F;
	}
	//p
	else if(hex == 0x19){
		return 0x70;
	}
	//q
	else if(hex == 0x10){
		return 0x71;
	}
	//r	
	else if(hex == 0x13){
		return 0x72;
	}
	//s	
	else if(hex == 0x1F){
		return 0x73;
	}
	//t
	else if(hex == 0x14){
		return 0x74;
	}
	//u	
	else if(hex == 0x16){
		return 0x75;
	}
	//v	
	else if(hex == 0x2F){
		return 0x76;
	}
	//w
	else if(hex == 0x11){
		return 0x77;
	}
	//x	
	else if(hex == 0x2D){
		return 0x78;
	}
	//y
	else if(hex == 0x15){
		return 0x79;
	}
	//z	
	else if(hex == 0x2C){
		return 0x7A;
	}
	//0	
	else if(hex == 0x0B){
		return 0x30;
	}
	//1	
	else if(hex == 0x02){
		return 0x31;
	}
	//2	
	else if(hex == 0x03){
		return 0x32;
	}
	//3	
	else if(hex == 0x04){
		return 0x33;
	}
	//4
	else if(hex == 0x05){
		return 0x34;
	}
	//5
	else if(hex == 0x06){
		return 0x35;
	}
	//6	
	else if(hex == 0x07){
		return 0x36;
	}
	//7	
	else if(hex == 0x08){
		return 0x37;
	}
	//8	
	else if(hex == 0x09){
		return 0x38;
	}
	//9
	else if(hex == 0x0A){
		return 0x39;
	}
	//Spacebar
	else if(hex == 0x39){
		return 0x20;
	}
}

//Checks to make sure byte is a valid character and
//Returns true is if it
int check_key(uint8_t key){

	if(key == 0x1E || key == 0x30 || key == 0x2E || key == 0x20 || key == 0x12 || key == 0x21 || key == 0x22
	 	|| key == 0x23 || key == 0x17 || key == 0x24 || key == 0x25 || key == 0x26 || key == 0x32 || key == 0x31
		 || key == 0x18 || key == 0x19 || key == 0x10 || key == 0x13 || key == 0x1F || key == 0x14
		 || key == 0x16 || key == 0x2F || key == 0x11 || key == 0x2D || key == 0x15 || key == 0x2C || key == 0x0B
		 || key == 0x02 || key == 0x03 || key == 0x04 || key == 0x05 || key == 0x06 || key == 0x07 || key == 0x08
		 || key == 0x09 || key == 0x0A || key == 0x39){

		return 1;

	}else{
		return 0;
	}

}


