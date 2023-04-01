/*
 * uart_tx.c
 *
 * Simple uart example, TX only.
 *
 * Created: 26-1-2023 17:28:49
 * Author: PeetHobby @PeetGaming
 *
 */ 
#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "uart_tx.h"	

void UART0_init(void)
{
	//initial UART
	USART0.CTRLB = USART_TXEN_bm;
	USART0.BAUD = USART0_BAUD_RATE(38400);					// set adjusted baud rate

	//Set TX(PB2) as output
	PORTB.DIR |= PIN2_bm;
	
	#if(PRINTF_ENABLE == 1)
	stdout = &USART_stream;					// UART stream to printf function
	#endif
}

// Normal
#if(PRINTF_ENABLE == 0)
	void UART0_send(uint8_t byte)
	{
		while (!(USART0.STATUS & USART_DREIF_bm))
		{
		}
		USART0.TXDATAL = byte;
	}

	void USART_sendString(char *str)
	{
		for(size_t i = 0; i < strlen(str); i++)
		{
			UART0_send(str[i]);
		}
	}
// With printf
#elif(PRINTF_ENABLE == 1)
	void USART0_sendChar(char c)
	{
		while (!(USART0.STATUS & USART_DREIF_bm))
		{
			;
		}
		USART0.TXDATAL = c;
	}

	static int USART0_printChar(char c, FILE *stream)
	{
		USART0_sendChar(c);
		return 0;
	}
#endif