/*
 * =================================================================
 * Filename:	entry.c
 * Description: kernel entry function
 * =================================================================
 */

#include "console.h"

int kern_entry(){
	console_clear();
	
	printk("Hello, OS kernel!\n");

	return 0;
}

