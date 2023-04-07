/*
 * uart_tx.h
 *
 *	Created: 26-1-2023 17:28:23
 *  Author: PeetHObby @PeetGaming
 *  Simple printf example
 */ 

#ifndef UART_PRINTF_H_
#define UART_PRINTF_H_

#define F_CPU 3333333		// 3.333MHz default clock, 20MHz / div6 = 3.3333...

#include <stdio.h>

//Macro: Baud rate configuration
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void UART0_printf_init(uint32_t baud);
void USART0_printf_sendChar(char c);
int USART0_printfChar(char c, FILE *stream);


#endif /* UART_PRINTF_H_ */