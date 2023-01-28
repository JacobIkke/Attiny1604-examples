/*
 * Attiny1604_external_pin_interrupt.c
 *
 * Created: 27-1-2023 23:29:24
 * Author : PeetGaming
 * This example call interrupt routine when PA0 pin is pulled low.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void PinInterrupt_init()
{
	PORTA.PIN0CTRL |= PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc; // active the pull-up resistor and ISC on falling edge. 
	PORTA_INTFLAGS |= PORT_INT0_bm; // Enable the interrupt on PA0
	sei(); // Enable global interrupts	
}

void GPIO_init(void)
{	
	PORTB.OUT |= PIN3_bm; // set PB3 to output
	PORTB.DIR |= PIN3_bm;
}

inline void toggle_led(void)
{
	PORTB.OUTTGL |= PIN3_bm; // Toggle PB3
}
int main(void)
{
    PinInterrupt_init(); 
	GPIO_init();
	
    while (1) 
    {
    }
}

ISR(PORTA_PORT_vect)
{
	toggle_led();
	PORTA.PIN0CTRL &= ~0x01; // Disable the pin change interrupt
	PORTA_INTFLAGS |= PORT_INT0_bm; // Clear the PA0 interrupt flag
}
