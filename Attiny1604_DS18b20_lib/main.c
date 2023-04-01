/*
 * Attiny1604 DS18b20 Demo 1.c
 *
 * Created: 1-4-2023 20:21:20
 * Author : PeetHobby @PeetGaming
 */ 

#define F_CPU 3333333							//3.3MHz default clock
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart_tx.h"							// TX lib

int main(void)
{
	UART0_init();
	ds18b20_init();
	uint8_t temp1 = 0;
	while (1)
	{
		//DS18b20
		start_meas();							// Start conversion
		_delay_ms(1000);						// Wait at least 750mS
		temp1 = read_meas();					// Get the temperature from the DS18b20
		char buf[12];							// Buffer for itoa function
		itoa(temp1,buf,10);						// convert int to string with itoa function
		
		//UART lib
		printf("Temperature : %d\n\r", temp1);	// TX only lib, printf enabled in h file. 
	}
}
