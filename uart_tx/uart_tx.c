/*
 * uart_tx.c
 *
 * Simple uart example, TX only.
 *
 * Created: 26-1-2023 17:28:49
 * Author: PeetHObby @PeetGaming
 *
 */ 
#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <string.h>
#include "uart_tx.h"		

//Baud rate configuration
#define BOOT_BAUD (38400) //range of: 38400 - 115200 BAUD with this code.

void init_uart(void)
{
	// See datasheet DS40002312A
	//initial UART
	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	// See AN2634 UART Source Code - Bootloader for tinyAVR 0- and 1-series, and megaAVR 0-series
	int32_t baud_reg_val  = (F_CPU * 64) / (BOOT_BAUD * 16);	// ideal BAUD register value
	int8_t sigrow_val = SIGROW.OSC20ERR3V;						// read signed error
	baud_reg_val *= (1024 + sigrow_val);						// sum resolution + error
	baud_reg_val += 512;										// compensate for rounding error
	baud_reg_val /= 1024;										// divide by resolution
	USART0.BAUD = (int16_t) baud_reg_val;						// set adjusted baud rate

	//Set TX(PB2) as output
	PORTB.DIR |= PIN2_bm;
}

void uart_send(uint8_t byte)
{
	// wait for the TX buffer to be empty, see Microchip app note TB3216 Send “Hello World” page 8
	while (!(USART0.STATUS & USART_DREIF_bm))
	{
	}
	// Send data, using the 8bit TXDATAL buffer.
	USART0.TXDATAL = byte;
}

void USART_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		uart_send(str[i]);
	}
}

void UART_sendInt(int *num)
{
	char buf[4];
	itoa(num,buf,10);
	UART_sendString(buf);
}
