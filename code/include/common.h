/*===============================================================
 * Filename:	common.h
 * Description:	define some data type
 * ==============================================================
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

//write one byte to port
void outb(uint16_t port, uint8_t value);

//read one byte from port
uint8_t inb(uint16_t port);

//write one word to port
void outw(uint16_t port, uint16_t value);

//read one word from port
uint16_t inw(uint16_t port);

#endif //INCLUDE_COMMON_H_
