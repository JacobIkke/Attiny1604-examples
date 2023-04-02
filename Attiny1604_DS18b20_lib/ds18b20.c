/*
 * DS18b20 library
 *
 * Created: 1-4-2023 17:28:49
 * Author: PeetHobby @PeetGaming
 *
 */ 

#define F_CPU 3333333				//3.3MHz default clock
#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20.h"

void ds18b20_init(void){
	PORT_1W.DIR |= PIN_1W;			// set Direction 
	PORT_1W.PULLUP |= (1<<3);		// Internal 10K pull up, is not always enough on it own. 
}

uint8_t Reset_1W(void){
	uint8_t i = 0;
	change_output();
	
	ONEWIRE_LOW;
	_delay_us(485); 
	
	change_input();
	_delay_us(70);
	
	if ((PORT_1W.IN & PIN_1W) == 1) { i = 1; }
	_delay_us(415);
	
	return i;
}

void change_output(void){
	PORT_1W.DIRSET |= PIN_1W;
}

void change_input(void){
	PORT_1W.DIRCLR |= PIN_1W;
}


uint8_t byte_wr_1W(uint8_t b){
	uint8_t j = 0;
	for (uint8_t i = 8; i > 0;i--){
		j = bit_io_1W( b & 1 );
		b >>= 1;
		if(j)
		b |= 0x80;	
	}	
	return b;
}

uint8_t byte_rd_1W(void){
	return byte_wr_1W(0xFF);
}

uint8_t  bit_io_1W(uint8_t bit){
	ONEWIRE_LOW;								//64us timing
	
	change_output();							// Change to Output
	_delay_us(4);								// 4us
	
	if(bit){change_input();}					// if bit is 1 Change pin to Input
	_delay_us(15);								// 19us-4us	= 15
	
	if ((PORT_1W.IN & PIN_1W) == 0) {			// read pin status, if 0 then bit = 0
		bit = 0;
	}
	_delay_us(45);								// 64us-19us = 45 //  45us + 15us + 4us = 64us Total
												
	change_input();
	return bit;
}

uint8_t rom_search_1W(uint8_t devs, uint8_t  *id){
	
	uint8_t i, j, next_dev;
	uint8_t rw_bit;

	if(Reset_1W())													// Reset
	return 0xFF;													// Error, no device was found
	
	byte_wr_1W(0xF0);												// ROM search command
	next_dev = 0x00;												// Unchanged on last device

		for (i = 64; i > 0;){										// ROM is 64bit long, "8b CRC - 48b SERIAL NUMBER - 8b FAMILY CODE (28h)"

			for (j = 8; j > 0; j--){								// Get the ROM byte by byte, 8bit at the time
	
				rw_bit = bit_io_1W(IO_IN);							// read bit
				
				if(bit_io_1W(IO_IN)){								// read complement bit, if 1 check if rw_bit also was 1, if so error. 
					if(rw_bit)										// if rw_bit is 1
					return 0xFE;									// 11 data error, return 0xFE
				}
				else{												// if rw_bit was okay
					if(!rw_bit){									// 00 = 2 devices
						if(devs > i || ((*id & 1) && devs != i)){
							rw_bit = 1;								// now 1
							next_dev = i;							// next pass 0
						}
					}
				}
				bit_io_1W(rw_bit);     								// 
				*id >>= 1;	
				if(rw_bit){											// 
					*id |= 0x80;
				}
				i--;
			}
			id++;
		}
  return next_dev;				// to continue search
}


void w1_command(uint8_t command, uint8_t *id){
	Reset_1W();
	if(id){ 
		byte_wr_1W(MATCH_ROM);			// to a single device
		for (uint8_t i = 8; i > 0; i--){
			byte_wr_1W(*id);
			id++;
		}
	}
	else{
		byte_wr_1W(SKIP_ROM);			// to all devices, SKIP_ROM = 0xCC
	}
	byte_wr_1W(command);				//0x44
}

void start_meas(void){
	change_input();
	if ((PORT_1W.IN & PIN_1W)){
		w1_command(CONVERT_T, 0 );
		ONEWIRE_HIGH;
		change_output();
	}
}

uint16_t read_meas(void){
	
	uint8_t id[8], devs; 
	int8_t sensorteller = 0;
	uint16_t temp = 0;
	uint8_t data[12];

	for(devs = SEARCH_FIRST; devs != LAST_DEVICE;){
		devs = rom_search_1W(devs, id);

		if( id[0] == 0x28 || id[0] == 0x10 ){			// id temperature sensors
			
			byte_wr_1W( READ );	
			#ifdef FULL_READ
				// Full read, all 9 bytes.
				for (uint8_t i = 0; i < 9; i++) {		// Read all 9 bytes of the scratchpad 
					data[i] = byte_rd_1W();
				}			
			#else 
				// Fast read, only first two bytes.
				// Those are the temperature bytes.  
				data[0] = byte_rd_1W();					// low byte 
				data[1] = byte_rd_1W();					// high byte
			#endif
			
			temp = (data[1] << 8) + data[0];			//take the two bytes from the response relating to temperature
			temp = temp>>4;								//divide by 16 to get pure Celsius readout
			
			#ifdef CELSIUS
			// If Celsius do nothing
			#else  
			// else Conversion to Fahrenheit
			temp=temp*1.8+32; 
			#endif
	
			sensorteller++;
		}
	}
	return temp;
}

