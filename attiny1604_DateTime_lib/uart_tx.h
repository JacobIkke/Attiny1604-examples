/*
 * uart_tx.h
 *
 * Created: 26-1-2023 17:28:23
 *  Author: PeetGaming
 */ 

#ifndef UART_H_
#define UART_H_

extern void UART_init(void);
extern void UART_sendChar(uint8_t byte);
extern void UART_sendString(char *str);

#endif /* UART_H_ */