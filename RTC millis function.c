/*
 * attiny1604_millis_lib.c
 *
 * Created: 6-4-2023 15:49:19
 * Author : PeetHobby @PeetGaming
 */ 

#define F_CPU 3333333		// 3.333MHz default clock, 20MHz / div6 = 3.3333...
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart_printf.h"

uint32_t millis_cnt; // Max value 0xffffffff = 4294967295 = 50 days 

//uint64_t millis; // Max value 0xffffffffffffffff = 18446744073709551615 = very very long, many years.
// one millis tick == +-950us
// 4294967295 * 980us = +-50 days

void Millis_clk_init(void);
uint32_t millis(void);
	
void Millis_clk_init(void){
	RTC.PITINTCTRL = RTC_PI_bm; // Enable the interrupt
	while (RTC.PITSTATUS > 0) { ; } // Wait until it's stable, 4 clk cycles.
	RTC.PITCTRLA = RTC_PERIOD_CYC4_gc | RTC_PITEN_bm; // Enable: enabled
}


ISR(RTC_PIT_vect){
	millis_cnt++;
	RTC.PITINTFLAGS = RTC_PI_bm;
}

uint32_t millis(){ 
	return millis_cnt; 
	}

int main(void)
{
	Millis_clk_init();
	sei();
	
	while (1)
	{
		uint32_t milliesNow = millis();

	}
}




