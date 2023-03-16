/*
 * DateTime example for Attiny1604
 *
 * Date and Time lib for the Attiny series 0, 1 and 2.
 * This example also uses the uart TX only lib, is included in this project directory.
 * PB2 = TX 38400 baud 8+1
 * datetime1604.c and datetime1604.h
 *
 * Created: 16-3-2023 19:20:40
 * Author : Peet
 */ 

#define F_CPU 3333333		//3.3MHz default clock
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart_tx.h"
#include "datetime1604.h"

int main(void)
{
	UART_init();			// default baud is 38400(cpu @3.33Mhz) (can be set to 38400-115200 in uart_tx.c) Set TX(PB2) as output
	RTC_init();			// setup of the RTC counter

	//set the time
	datetimenow.second = 20;	// Set seconds
	datetimenow.minute = 39;	// Set Minutes
	datetimenow.hour = 15;		// Set Hours
	
	//set the time
	datetimenow.day = 16;		// Set day
	datetimenow.month = 3;		// Set Month
	datetimenow.year = 23; 		// Set year, 8bit int we use format like this 20xx
	
    while (1) 
    {
		// Time
		uint8_t hours = datetimenow.hour;	// Get the Hours
		UART_sendInt(hours);			// send as integer
		UART_sendChar(0x3A);			// 0x3A double dot :
		
		uint8_t minutes = datetimenow.minute;	// Get the Minutes
		UART_sendInt(minutes);			// send as integer
		UART_sendChar(0x3A);			// 0x3A = double dot :
		
		uint8_t secs = datetimenow.second;	// Get the Seconds
		UART_sendInt(secs);			// send as integer
		UART_sendChar(0x20); 			// 0x20 = space
		
		// Date
		uint8_t days = datetimenow.day; 	// Get the Days
		UART_sendInt(days);			// send as integer
		UART_sendChar(0x2D); 			// 0x2D = line -
				
		uint8_t months = datetimenow.month;	// Get the Months
		UART_sendInt(months);			// send as integer
		UART_sendChar(0x2D); 			// 0x2D = line -
		
		uint8_t years = datetimenow.year;	// Get the Years, stored in 8bit int, we only count the last two numbers 20xx of the year.
		UART_sendString("20");			// Print 20 first so we see the correct year in the console
		UART_sendInt(years);			// send as integer 

		UART_sendChar(0x0A); 			//LF line feed or newline /n
		UART_sendChar(0x0D); 			//CR Carriage return /n
		
		_delay_ms(1000);		
    }
}

