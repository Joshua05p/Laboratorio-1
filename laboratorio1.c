/*
 * Laboratorio.c
 *
 * Created: 21/04/2025 16:46:36
 * Author : Joshua
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Display.h"

/****************************************/
// Function prototypes
void confi_timer1();
int contador = 6;
int jugador1 = 0;
int jugador2 = 0;
void setup();
int carrera = 0;
/****************************************/
// Main Function
int main(void) {
	setup();
	confi_timer1();
	PORTD = 0xFF;
	while (1)
	{

	}
}

/****************************************/
// NON-Interrupt subroutines
void setup(void) {
	//SALIDAS
	DDRD = 0xFF;
	DDRC |= 0x0F;
	DDRB |= 0x0F;
	//Entradas
	DDRB &= ~(1<<DDB4);
	PORTB |= (1 << PORTD4);
	DDRB &= ~(1<<DDB5);    
	PORTB |= (1<<PORTB5); 
	DDRC &= ~(1<<DDC4); 
	PORTC |= (1<<PORTC4); 

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT4);
	PCMSK0 |= (1 << PCINT5);
	
	PCICR |= (1 << PCIE1); 
	PCMSK1 |= (1 << PCINT12);
	
	sei();
}

void confi_timer1(){
//CONFIGURACION TIMER1
{
	TCCR1A = 0x00;
	TCCR1B = 0x00;

	TCNT1 = 31250;            

	TIMSK1 = (1 << TOIE1);

	sei();
	}
}


/****************************************/
// Interrupt routines
//CONTEO REGRESIVO
ISR(TIMER1_OVF_vect)
{
	TCNT1 = 31250;
	if (contador == 0){
		contador = 6;
		TCCR1B = 0x00;
		carrera = 1;
		PORTD = 0xFF;
		} else {
		contador = contador - 1;
		f_display(contador);
	}

}
//BOTON DE INICIO
ISR(PCINT0_vect)
	{
		if (!(PINB & (1 << PINB4)))
		{
			TCCR1B = (1 << CS12);
			PORTB = 0x00;
			PORTC = 0x00;
		} else if (carrera == 1){
			if (!(PINB & (1 << PINB5)))
				{
					//contador 1
					jugador1++;
					jugador1 &= 0x0F;
				if ( (jugador1 & 0x0F) == 0x0F )
				{
					PORTB = 0x00;
					PORTC = 0x0F;
					PORTD = 0xF9;
					carrera = 0;
					}else{
					PORTC = (PORTC & 0xF0) | (jugador1 & 0x0F);
				}
	
				}
	}
		

}
//BOTONES DE JUGADORES
ISR(PCINT1_vect)
{
	if (carrera == 1){
			if (!(PINC & (1 << PINC4)))
			{
				//contador 2
				jugador2++;
				jugador2 &= 0x0F;
				if ( (jugador2 & 0x0F) == 0x0F )
				{
					PORTC = 0x00;
					PORTB = 0x0F;
					PORTD = 0xA4;
					carrera = 0;
				}else{
					PORTB = (PORTB & 0xF0) | (jugador2 & 0x0F);
				}
			}
	}
}
