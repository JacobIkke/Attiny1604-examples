/*
 * Atiny1604_UART_interrupt.c
 *
 * Created: 18-5-2023 19:10:29
 * Author : PeetHobby @PeetGaming
 */ 
// Includes
#include <avr/io.h>
#include "avr/interrupt.h"

// Defines
#define BAUD_RATE 9600
#define F_CPU 3333333
#define UART_RX_BUFFER_SIZE 64	// Size of the RX buffer, can chance it if you like

// Macros
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// Global Variables
volatile char uartRxBuffer[UART_RX_BUFFER_SIZE];
volatile uint8_t uartRxIndex = 0;

// Function prototypes
ISR(USART0_RXC_vect);
void UART_init(void);
void UART_sendByte(uint8_t data);
void UART_sendString(const char* str);

// interrupts
ISR(USART0_RXC_vect) {
	cli();									// Disable global interrupt
	
	char receivedData = USART0.RXDATAL;					// Store received char
	// Store received data in the buffer
	if (uartRxIndex < UART_RX_BUFFER_SIZE) {				// check if buffer is not already full
		uartRxBuffer[uartRxIndex] = receivedData;			// Put the received char in the Rx buffer
		uartRxIndex++;							// Increase Rx index 
	}
	
	sei();									// Enable global interrupt
}

// Functions
void UART_init(void) {
	
	PORTB.DIR |= PIN2_bm; 							// Set TX(PB2) as output
	PORTB.DIR &= ~PIN3_bm;							// Set RX(PB3) as input
	PORTB.PIN3CTRL |= PORT_PULLUPEN_bm;					// Enable pull-up resistor for RX pin
		
	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;				// Enable RX and TX of USART0
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(115200);			// 300-115200 baud rate with the 3.333Mhz default CPU clock.
	USART0.CTRLA |= USART_RXCIE_bm;						// Enable UART receive interrupt
}

void UART_sendByte(uint8_t data) {
	while (!(USART0.STATUS & USART_DREIF_bm));				// Wait for the transmit buffer to be empty
	USART0.TXDATAL = data;							// Put the data into the transmit buffer
}

void UART_sendString(const char* str) {
	// Iterate through each character until a null terminator is encountered
	while (*str != '\0') {							// Loop until the end of string '\0'
		UART_sendByte(*str);						// Send each character
		str++;								// Move to the next character
	}
}

uint8_t UART_receiveByte() {
	while (!(USART0.STATUS & USART_RXCIF_bm));				// Wait for the data to be received
	return USART0.RXDATAL;							// Return the received data
}


// Program code start here
int main(void){
	
	UART_init();								// Initial the UART.
	sei();									// Enable the Global Interrupt Enable flag so that interrupts can be processed
	
	//Just a simple delay loop
	for (uint32_t i=0; i < 0xffff; i++){ asm("nop");	}
	
	UART_sendString("Please type something, I will echo it back\n\r");	// Send string with UART
	
   	 while (1) {
		
		// Check if RX buffer has received some bytes
		if (uartRxIndex > 0) {						// Check if we received something in the RX buffer 
	
			for (int i=0; i < uartRxIndex; i++){			// loop trough all bytes in the RX buffer
				UART_sendByte(uartRxBuffer[i]);			// Send the received byte back to TX
			}
			
			UART_sendString("\n\r");				// New line
			uartRxIndex = 0;					// Reset the RX index 
		}
				
		//Just a simple delay loop
		for (uint32_t i=0; i < 0xffff; i++){ asm("nop");	
	}
		
    }
}

