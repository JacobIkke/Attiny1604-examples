/*
 * Attiny1604_uart.c
 *
 * Created: 26-1-2023 15:24:23
 * Author : PeetHobby @PeetGaming
 */ 
#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart_tx.h" 

int main(void)
{
	init_uart();

    while (1) 
    {	
		USART_sendString("Hello World!\r\n");
		_delay_ms(1000);	
    }
}

