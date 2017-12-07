/*=======================================================
 * Filename:	common.c
 * Description:	R/W to port functoins
 * ======================================================
 */

#include "common.h"

//write one byte to port
inline void outb(uint16_t port, uint8_t value){
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

//read one byte from port
inline uint8_t inb(uint16_t port){
	uint8_t ret;
	
	asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));

	return ret;
}

//write one word to port
inline void outw(uint16_t port, uint16_t value){
	asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}
