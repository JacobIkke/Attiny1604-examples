/*
 * attiny1604_input_GPIO.c
 *
 * Created: 27-1-2023 16:05:25
 * Author : Peethobby
 */ 

#define F_CPU 3333333
#include <util/delay.h>
#include <avr/io.h>


void gpio_init(void)
{
	// PORTA bit 0-7
	PORTA.OUT  |= PIN0_bm; //PA0 as input
	PORTA.DIR &= ~ PIN0_bm;
	PORTA.PIN0CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; // Set pull up, and trigger on raising and falling edge

	// PORTB bit 0-3
    	PORTB.OUT |= PIN2_bm; // PB2 as output
    	PORTB.DIR |= PIN2_bm;
}

void toggle_led(void)
{
	PORTB.OUTTGL |= PIN2_bm; // Toggle PB2 pin
}

int main(void)
{
	gpio_init();
	
   	 while (1) 
    	{
		if(~PORTA.IN & PIN0_bm) // check PORTA for changes, bitmask pin0 so we get only that bit.
		{
			toggle_led();
			_delay_ms(200);
		}	
    	}
}

