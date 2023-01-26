/*
 * uart_tx.h
 *
 * Created: 26-1-2023 17:28:23
 *  Author: PeetHObby @PeetGaming
 */ 

#ifndef UART_H_
#define UART_H_

extern void init_uart(void);
extern void uart_send(uint8_t byte);
extern void USART_sendString(char *str);

#endif /* UART_H_ */