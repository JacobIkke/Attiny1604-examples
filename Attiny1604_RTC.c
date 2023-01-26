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

void RTC_init(void)
{
	uint8_t temp;
	
	// RTC is already disabled form the start, so we don't have to disable it again. 
	// Only need to disable a timer when it's already running and you want change some timer settings.
	/*
	temp = CLKCTRL.OSC32KCTRLA;
	temp &= ~CLKCTRL_LOCKEN_bm; // Disable rtc timer
	ccp_write_io((void*)&CLKCTRL.OSC32KCTRLA, temp);
	while(CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)
	{
	}
	*/
	
	temp = CLKCTRL.OSC32KCTRLA;
	temp |= CLKCTRL_LOCKEN_bm; // Enable rtc timer
	ccp_write_io((void*)&CLKCTRL.OSC32KCTRLA, temp);
	while (RTC.STATUS > 0)
	{

	}

	RTC.PITINTCTRL = RTC_PI_bm; /* Periodic Interrupt: enabled */
	RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm; /* Enable: enabled */
}

void LED_init(void)
{
	PORTB.OUT |= PIN2_bm;
	PORTB.DIR |= PIN2_bm;
}

inline void LED_toggle(void)
{
	PORTB.OUTTGL |= PIN2_bm;
}

ISR(RTC_PIT_vect)
{
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


