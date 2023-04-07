/*
 * uart_tx.c
 *
 * Simple printf example, TX only.
 *
 * Created: 26-1-2023 17:28:49
 * Author: PeetHobby @PeetGaming
 *
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#include "uart_printf.h"	

static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printfChar, NULL, _FDEV_SETUP_WRITE);

void UART0_printf_init(uint32_t baud){
	USART0.CTRLB = USART_TXEN_bm; //Enable TX UART0
	USART0.BAUD = USART0_BAUD_RATE(baud); // Set Baud rate
	PORTB.DIR |= PIN2_bm;	//Set TX(PB2) as output
	stdout = &USART_stream;	// UART stream to printf function			
}

void USART0_printf_sendChar(char c){
	while (!(USART0.STATUS & USART_DREIF_bm)){}
	USART0.TXDATAL = c;
}

int USART0_printfChar(char c, FILE *stream){
	USART0_printf_sendChar(c);
	return 0;
}