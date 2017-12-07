/*==========================================================
 * Filename:	console.h
 * Description:	head file about some screen console control functions
 *==========================================================
 */

#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"

typedef
enum real_color{
	rc_black = 0,
	rc_blue = 1,
	rc_green = 2,
	rc_cyan = 3,
	rc_red = 4,
	rc_megenta = 5,
	rc_brown = 6,
	rc_light_grey = 7,
	rc_dark_grey = 8,
	rc_light_blue = 9,
	rc_light_green = 10,
	rc_light_cyan = 11,
	rc_light_red = 12,
	rc_light_megenta = 13,
	rc_light_brown = 14,
	rc_white = 15
}real_color_t;

//clear the console
void console_clear();

//print one character in console with color
void console_putc_color(char c, real_color_t back, real_color_t fore);

//print one string ends with \0(default with black background and white font color)
void console_write(char* cstr);

//print one string ends with \0
void console_write_color(char* cstr, real_color_t back, real_color_t fore);

//print one hex number
void console_write_hex(uint32_t n, real_color_t back, real_color_t fore);

//print one dec number
void console_write_dec(uint32_t n, real_color_t back, real_color_t fore);

#endif //INCLUDE_CONSOLE_H_
