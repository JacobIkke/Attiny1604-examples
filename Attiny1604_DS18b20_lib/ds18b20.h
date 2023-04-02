/*
 * DS18b20 library
 *
 * Created: 1-4-2023 17:28:49
 * Author: PeetHobby @PeetGaming
 *
 */ 

#ifndef DS18B20_H_
#define DS18B20_H_

// Port and pin settings 
#define PORT_1W 		PORTA
#define PIN_1W			PIN4_bm
#define PULLUP			PIN4CTRL
#define PIN_NUM			4

// Software Settings
//#define FULL_READ			// comment this out for fast read
#define CELSIUS				// comment this out for Fahrenheit

// Marco's
#define ONEWIRE_LOW		PORT_1W.OUTCLR = (1<<PIN_NUM); // set LOW  
#define ONEWIRE_HIGH	PORT_1W.OUTSET = (1<<PIN_NUM); // set high 

// Defines
#define MATCH_ROM		0x55
#define SKIP_ROM		0xCC
#define	SEARCH_ROM		0xF0

#define CONVERT_T		0x44		
#define READ			0xBE
#define WRITE			0x4E
#define EE_WRITE		0x48
#define EE_RECALL		0xB8

#define	SEARCH_FIRST	0xFF		
#define	PRESENCE_ERR	0xFF
#define	DATA_ERR		0xFE
#define LAST_DEVICE		0x00		

#define IO_IN			1
#define IO_OUT			0

// Functions
void ds18b20_init(void);
uint8_t Reset_1W(void);
void change_input(void);
void change_output(void);
unsigned char bit_io_1W(uint8_t b);
uint8_t byte_wr_1W(unsigned char b);
uint8_t byte_rd_1W(void);
unsigned char rom_search_1W(unsigned char diff, unsigned char  *id);
void command_1W(unsigned char command, unsigned char  *id);
void start_meas(void);
uint16_t read_meas(void);

#endif /* DS18B20_H_ */

