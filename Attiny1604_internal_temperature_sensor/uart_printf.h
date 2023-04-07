/*
 * uart_tx.h
 *
 *	Created: 26-1-2023 17:28:23
 *  Author: PeetHObby @PeetGaming
 *  Simple printf example
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdio.h>

//Baud rate configuration
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void UART0_printf_init(void);
void USART0_printf_sendChar(char c);
static int USART0_printfChar(char c, FILE *stream);

static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printfChar, NULL, _FDEV_SETUP_WRITE);

#endif /* UART_H_ */