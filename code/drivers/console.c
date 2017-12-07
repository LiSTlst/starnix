/*=====================================================
 * Filename:	console.c
 * Description:	functions of screen console controling
 * ====================================================
 */

#include "console.h"
#include "common.h"

//VGA console buffer start at 0xB8000 in memory
static uint16_t* video_memory = (uint16_t*)0xB8000;

//cursor location in console
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//move the cursor in console
static void move_cursor(){
	//the size of VGA console is 80 * 25 charactors
	uint16_t cursor_location = cursor_y * 80 + cursor_x;
	
	//tell VGA the location of cursor by put the localtion to VGA port 0x3D4 
	outb(0x3D4, 14);			//put the high 8 bits of location to register 14
	outb(0x3d4, cursor_location >> 8);
	outb(0x3d4, 15);			//put the low 8 bits of locatoin to register 15
	outb(0x3d5, cursor_location);
}

//scroll the console
static void scroll(){
	//set the blank as space with black background and white font color
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);		//ASCII space:0x20
	//when the cursor_y = 25, you will need scroll the screen
	if(cursor_y >= 25){
		int i;
		//cover the line with the next line, equal to move all the lines on console one line up
		for(i = 0; i < 24 * 80; i++){
			video_memory[i] = video_memory[i + 80];
		}
		//cover the last line with blanks
		for(i = 24 * 80; i < 25 * 80; i++){
			video_memory[i] = blank;
		}

		cursor_y = 24;
	}
}

//clear the console
void console_clear(){
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);
	
	int i;
	for(i = 0; i < 80 * 25; i ++){
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

//print a charactor with color
void console_putc_color(char c, real_color_t back, real_color_t fore){
	uint8_t back_color = (uint8_t)back;
	uint8_t fore_color = (uint8_t)fore;
	
	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
	uint16_t attribute = attribute_byte << 8;

	//ASCII 0x08:back
	//ASCII 0x09:tab
	if(c == 0x08 && cursor_x){
	       cursor_x --;
	}else if(c == 0x09){
		cursor_x = (cursor_x + 8) & ~(8-1);
	}else if(c == '\r'){
		cursor_x = 0;
	}else if(c == '\n'){
		cursor_x = 0;
		cursor_y ++;
	}else if(c >= ' '){
	       video_memory[cursor_y * 80 + cursor_x] = c | attribute;
	       cursor_x ++;
	}
	
	if(cursor_x >= 80){
		cursor_x = 0;
		cursor_y ++;
	}
		
	scroll();
	
	move_cursor();
}

//print string end with \0 defualt with black background and white font color
void console_write(char* cstr){
	while(*cstr){
		console_putc_color(*cstr++, rc_black, rc_white);
	}
}

//print string end with \0 with color
void console_write_color(char* cstr, real_color_t back, real_color_t fore){
	while(*cstr){
		console_putc_color(*cstr++, back, fore);
	}
}

//print a hex number
void console_write_hex(uint32_t n, real_color_t back, real_color_t fore){
	int tmp;
	char noZeroes = 1;

	console_write_color("0x", back, fore);

	int i;
	for(i =28; i >= 0; i -= 4){
		tmp = (n >> i) & 0xF;
		if(tmp == 0 && noZeroes != 0){
			continue;
		}
		noZeroes = 0;
		if(tmp >= 0xA){
			console_putc_color(tmp-0xA+'a', back, fore);
		}else{
			console_putc_color(tmp+'0', back, fore);
		}
	}
}

//print a dec number
void console_write_dec(uint32_t n, real_color_t back, real_color_t fore){
	if(n == 0){
		console_putc_color('0', back, fore);
		return;
	}

	uint32_t acc = n;
	char c[32];
	int i = 0;
	while(acc > 0){
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;

	int j = 0;
	while(i >= 0){
		c2[i--] = c[j++];
	}

	console_write_color(c2, back, fore);
}

