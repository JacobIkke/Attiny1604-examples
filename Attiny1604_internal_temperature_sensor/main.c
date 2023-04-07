/*
 * Attiny1604_Internal_temperture_sensor.c
 *
 * Created: 5-4-2023 15:57:59
 * Author : peetHobby @PeetGaming
 *
 * Example code of how you can read internal temperature sensor of the attiny1604
 * The datasheet says that those sensors are +-10c accurate, but out of experience with many AVR's in past decades 
 * I learned that those sensors are much more accurate, +-1 degree C. 
 */ 

#include "uart_printf.h"	// Put uart_printf.h and uart_printf.c in same directory as the main.c. 
#include <util/delay.h>		// Need to be above uart_printf.h because F_CPU
#include <avr/io.h>			// F_CPU is declared in uart_printf.h 

// The internal 1.1 V vref must be selected to read the internal temperature sensor correctly.
void set_vref_1v1(void){
	VREF_CTRLB = 0 << VREF_ADC0REFEN_bp;	// Disable ADC reference
	VREF_CTRLA = VREF_ADC0REFSEL_1V1_gc;	// Change the vref, this case to 1.1v
	VREF_CTRLB = 1 << VREF_ADC0REFEN_bp;	// Enable ADC reference
}

void ADC0_init(void){
	// CLK_ADC must run between 50Khz and 1.5MHz
	ADC0.CTRLC = ADC_PRESC_DIV8_gc  |		// CLK_PER divided by 8, 3.3Mhz / 8 = 416Khz. The ADC CLK must be between 50K and 1.5MHz 
				ADC_REFSEL_INTREF_gc |		// Select the internal vref
				0 << ADC_SAMPCAP_bp;		// Sample Capacitance off

	ADC0.CTRLA = 1 << ADC_ENABLE_bp  |		// Enable the ADC
				 0 << ADC_FREERUN_bp |		// ADC Freerun mode off
				 ADC_RESSEL_10BIT_gc |		// Set the ADC in 10-bit mode 
				 0 << ADC_RUNSTBY_bp;		// Run standby mode off
				 
	ADC0.CTRLA |= ADC_ENABLE_bm; // Enable the ADC
}


int main(void)
{
	set_vref_1v1();
	ADC0_init();
	UART0_printf_init(115200);
	
	while (1)	{
		
		// start an ADC conversion.
		// A conversion(10bit) takes 13 CLK_ADC, max 115Ksps. 
		// 1.5MHz/13=115Ksps. 8b ADC can sample a bit faster.
		ADC0.MUXPOS  = ADC_MUXPOS_TEMPSENSE_gc;				// Switch the MUX to internal temperature sensor
		ADC0.COMMAND = ADC_STCONV_bm;						// start ADC conversion
		while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)){ ; }		// wait for the conversion to be done
		
		// Get the temperature for the ADC
		int8_t sigrow_offset = SIGROW.TEMPSENSE1;			// Read signed value from signature row
		uint8_t sigrow_gain = SIGROW.TEMPSENSE0;			// Read unsigned value from signature
		uint16_t adc_reading = ADC0.RES;					// ADC conversion result with 1.1 V internal
		uint32_t temp = adc_reading - sigrow_offset;
		temp *= sigrow_gain;								// Result might overflow 16 bit variable (10bit+8bit)
		temp += 0x80;										// Add 1/2 to get correct rounding on division below
		temp >>= 8;											// Divide result to get Kelvin
		uint16_t Kelvin = temp - 4;							// Store the results in variable and some fine tune, can sub/add couple of degree. 

		uint16_t Celsius2 = Kelvin - 273;					// Convert Kelvin to Celsius
		uint16_t Fahrenheit  = ((Kelvin - 273) * 1.8) + 32; // Convert Kelvin to Fahrenheit
		
		// Print some info and results
		printf("sig_offset		: %3d\n\r", sigrow_offset);
		printf("sig_gain		: %3d\n\r", sigrow_gain);
		printf("adc_reading		: %3d\n\r", adc_reading);
		printf("Kelvin			: %3dk\n\r", Kelvin);		
		printf("Celsius			: %3dc\n\r", Celsius2);
		printf("Fahrenheit		: %3df\n\r\n\r", Fahrenheit);
		_delay_ms(2000);
	}
}


