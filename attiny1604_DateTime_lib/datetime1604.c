/*
 * rtc_1604.c
 *
 * Created: 27-1-2023 19:24:00
 *  Author: PeetGaming
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include "datetime1604.h"


void RTC_init(void)
{
	// RTC is already disabled form the start, so we don't need to disable it first.
	// Only need to disable a timer when it's already running and want to change it.
	uint8_t temp;
	
	temp = CLKCTRL.OSC32KCTRLA;
	temp |= CLKCTRL_LOCKEN_bm;
	ccp_write_io((void*)&CLKCTRL.OSC32KCTRLA, temp);
	while (RTC.STATUS > 0)
	{
	}

	RTC.PITINTCTRL = RTC_PI_bm; /* Periodic Interrupt: enabled */
	RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm; /* Enable: enabled */
	sei();
}


ISR(RTC_PIT_vect)
{
	datetimenow.second++;
	// Time
	// Seconds
	if(datetimenow.second >= 60){
		datetimenow.second = 0;
		datetimenow.minute++;
	}
	// Minutes
	if(datetimenow.minute >= 60){
		datetimenow.minute = 0;
		datetimenow.hour++;
	}
	// Hours
	if(datetimenow.hour >= 24){
		datetimenow.hour = 0;
		datetimenow.day++;
	}
	// Date
	// Number of days in the months
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//Months
	if(datetimenow.day > days_in_month[datetimenow.month]){  //odd months
		datetimenow.day = 0;
		datetimenow.month++;
	}
	//years
	if(datetimenow.month >= 12){
		datetimenow.month = 0;
		datetimenow.year++;
	}
	RTC.PITINTFLAGS = RTC_PI_bm;
}


