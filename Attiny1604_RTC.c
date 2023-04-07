/*
 *Attiny1604_RTC.c
 *
 * Created: 26-1-2023 00:58:54
 * Author : PeetHobby (peetGaming)
 * TB3213 - Getting Started with Real-Time Counter (RTC)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

void RTC_init(void);
void LED_init(void);
inline void LED_toggle(void);

void RTC_init(void){
	RTC.PITINTCTRL = RTC_PI_bm; // Enable the interrupt
	while (RTC.PITSTATUS > 0) { ; } // Wait until it's stable, 4 clk cycles.
	RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm; // Set period and Enable the RTC
}

void LED_init(void){
	PORTB.DIR |= PIN0_bm ;
}

inline void LED_toggle(void){
	PORTB.OUTTGL |= PIN0_bm;
}

ISR(RTC_PIT_vect){
	RTC.PITINTFLAGS = RTC_PI_bm;
	LED_toggle();
}

int main(void)
{
	LED_init();
	RTC_init();
	sei();
	
	while (1)
	{
	
	}
}

