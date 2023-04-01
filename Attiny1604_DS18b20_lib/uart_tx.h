/*
 * uart_tx.h
 *
 * Created: 26-1-2023 17:28:23
 *  Author: PeetHObby @PeetGaming
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdio.h>

//Baud rate configuration
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

//printf support
#define PRINTF_ENABLE    1  // 1 = Printf enabled, 0 = disabled

void UART0_init(void);
void UART0_send(uint8_t byte);
void USART0_sendString(char *str);
void USART0_sendChar(char c);
static int USART0_printChar(char c, FILE *stream);

#if(PRINTF_ENABLE == 1)
static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printChar, NULL, _FDEV_SETUP_WRITE);
#endif

#endif /* UART_H_ */