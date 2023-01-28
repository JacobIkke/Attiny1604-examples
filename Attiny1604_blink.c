/*
 * tinyAVR1604 blink v1.c
 *
 * Created: 25-1-2023 15:11:39
 * Author : PeetGaming (PeetHobby)
 *
 * TB3229 - Getting Started with General Purpose Input/Output (GPIO)
 * TB3262 - AVR1000b: Getting Started with Writing C-Code for AVR® MCUs
 *
 * iotn1604.h has all the naming conventions for the attiny1604.
 *
 */ 

#define F_CPU 3333333 // The default clock is 3.3Mhz
#include <util/delay.h>
#include <avr/io.h>


int main(void) {

	PORTB.DIR |= PIN2_bm;  // set PB2 to output
	
	while (1){
	
		PORTB_OUTSET = (1<<2); // set HIGH 
		_delay_ms(1000);
	
		PORTB_OUTCLR = (1<<2); // set LOW 
		_delay_ms(1000);
	}

}
