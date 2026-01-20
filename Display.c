/*
 * Display.c
 *
 * Created: 19/01/2026 21:45:58
 *  Author: perez
 */ 
#include "Display.h"

int display[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};


void f_display(int valor)
{
		PORTD = display[valor];

}
