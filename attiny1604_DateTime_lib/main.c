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
	UART_init();	// default baud is 38400(cpu @3.33Mhz) (can be set to 38400-115200 in uart_tx.c) Set TX(PB2) as output
	RTC_init();		// setup of the RTC counter

	//set the time
	datetimenow.second = 20;
	datetimenow.minute = 39;
	datetimenow.hour = 15;
	
	//set the time
	datetimenow.day = 16;
	datetimenow.month = 3;
	datetimenow.year = 23; // 20xx
	
    while (1) 
    {
		// Time
		uint8_t hours = datetimenow.hour;	// Hours
		UART_sendInt(hours);				// send integer
		UART_sendChar(0x3A);				// 0x3A double dot :
		
		uint8_t minutes = datetimenow.minute;
		UART_sendInt(minutes);
		UART_sendChar(0x3A);				 // 0x3A = double dot :
		
		uint8_t secs = datetimenow.second;
		UART_sendInt(secs);
		UART_sendChar(0x20); // 0x20 = space
		
		// Date
		uint8_t days = datetimenow.day; // Days
		UART_sendInt(days);
		UART_sendChar(0x2D); //
				
		uint8_t months = datetimenow.month;	// Months
		UART_sendInt(months);
		UART_sendChar(0x2D); // 0x2D = line -
		
		uint8_t years = datetimenow.year;
		UART_sendString("20");
		UART_sendInt(years);

		UART_sendChar(0x0A); //LF line feed or newline /n
		UART_sendChar(0x0D); //CR Carriage return /n
		
		_delay_ms(1000);		
    }
}

