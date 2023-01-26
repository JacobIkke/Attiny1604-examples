/*
 * attiny1604 minimal RTC.c
 *
 * Created: 26-1-2023 00:58:54
 * Author : jacob
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

void RTC_init(void);
void LED0_init(void);
inline void LED0_toggle(void);

void RTC_init(void)
{
	uint8_t temp;
	
	temp = CLKCTRL.OSC32KCTRLA;
	temp |= CLKCTRL_LOCKEN_bm;
	ccp_write_io((void*)&CLKCTRL.OSC32KCTRLA, temp);
	while (RTC.STATUS > 0)
	{

	}

	RTC.PITINTCTRL = RTC_PI_bm; /* Periodic Interrupt: enabled */
	RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm; /* Enable: enabled */
}

void LED0_init(void)
{
	PORTB.OUT |= PIN2_bm;
	PORTB.DIR |= PIN2_bm;
}

inline void LED0_toggle(void)
{
	PORTB.OUTTGL |= PIN2_bm;
}

ISR(RTC_PIT_vect)
{
	RTC.PITINTFLAGS = RTC_PI_bm;
	LED0_toggle();
}

int main(void)
{
	LED0_init();
	RTC_init();
	sei();
	
	while (1)
	{
		
	}
}


