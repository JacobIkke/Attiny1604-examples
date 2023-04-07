/*
 * uart_tx.c
 *
 * Simple printf example, TX only.
 *
 * Created: 26-1-2023 17:28:49
 * Author: PeetHobby @PeetGaming
 *
 */ 

#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "uart_printf.h"	

void UART0_printf_init(void){
	//initial UART
	USART0.CTRLB = USART_TXEN_bm;
	USART0.BAUD = USART0_BAUD_RATE(9600);		// adjusted baud rate her

	//Set TX(PB2) as output
	PORTB.DIR |= PIN2_bm;
	// UART stream to printf function
	stdout = &USART_stream;					
}

void USART0_printf_sendChar(char c){
	while (!(USART0.STATUS & USART_DREIF_bm)){}
	USART0.TXDATAL = c;
}

static int USART0_printfChar(char c, FILE *stream){
	USART0_printf_sendChar(c);
	return 0;
}