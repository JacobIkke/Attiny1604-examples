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

#define F_CPU 3333333		// 3.333MHz default clock, 20MHz / div6 = 3.3333... 
#include <util/delay.h>		// standard GCC lib
#include <avr/io.h>			// standard GCC lib
#include "uart_printf.h"	// Put uart_printf.h and uart_printf.c in same directory as the main.c. 

// The internal 1.1 V vref must be selected to read the internal temperature sensor correctly.
void set_vref_1v1(void){
	VREF_CTRLB = 0 << VREF_ADC0REFEN_bp;	// Disable ADC reference
	VREF_CTRLA = VREF_ADC0REFSEL_1V1_gc;	// Change the vref, this case to 1.1v
	VREF_CTRLB = 1 << VREF_ADC0REFEN_bp;	// Enable ADC reference
}

void ADC0_init(){
	// CLK_ADC must between 50K and 1.5MHz for 10bit ADC
	ADC0.CTRLC = ADC_PRESC_DIV8_gc  |		// CLK_PER divided by 32, 3.3Mhz / 32 = 416Khz CLK_ADC. CLK_ADC must between 50K and 1.5MHz 
				ADC_REFSEL_INTREF_gc |		// Select internal reference 
				0 << ADC_SAMPCAP_bp;		// Sample Capacitance Selection: disabled 

	ADC0.CTRLA = 1 << ADC_ENABLE_bp  |		// ADC Enable: enabled 
				 0 << ADC_FREERUN_bp |		// ADC Freerun mode: disabled 
				 ADC_RESSEL_10BIT_gc |		// 10-bit mode 
				 0 << ADC_RUNSTBY_bp;		// Run standby mode: disabled 
				 
	// Enable the ADC
	ADC0.CTRLA |= ADC_ENABLE_bm;
}


int main(void)
{
    set_vref_1v1();
	ADC0_init();
	UART0_printf_init();
	
    while (1) 
    {
		// start an ADC conversion. 
		ADC0.MUXPOS  = ADC_MUXPOS_TEMPSENSE_gc;			// Switch the MUX to internal temperature sensor
		ADC0.COMMAND = ADC_STCONV_bm;					// start ADC conversion
		while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)){ ; }	// wait for the conversion to be done
		//A conversion(10bit) takes 13 CLK_ADC, max 115Ksps. 1.5MHz / 13 = 115Ksps. 8bit can sample a bit faster.
			
		// 1. My shorter version to convert the temp sensor ADC data to Celsius.
		uint16_t temp_ADC = ADC0.RES;					// store the result in temp_ADC variable
		uint16_t offset = 500;							// Offset is usually around the -500, can use this to fine tune the temperature
		float slope = 0.85;								// If temperature climbs to fast or to slow you can use this to fine adjust the slope.
		uint16_t Celsius1 = (temp_ADC-offset) * slope;	// the tinyAVR has a hardware multiplier, so no need to avoid multiplying. :)
		
		// 2. From the datasheet page  381
		int8_t sigrow_offset = SIGROW.TEMPSENSE1;		// Read signed value from signature row
		uint8_t sigrow_gain = SIGROW.TEMPSENSE0;		// Read unsigned value from signature
		uint16_t adc_reading = ADC0.RES;				// ADC conversion result with 1.1 V internal
		uint32_t temp = adc_reading - sigrow_offset; 
		temp *= sigrow_gain;							// Result might overflow 16 bit variable (10bit+8bit)
		temp += 0x80;									// Add 1/2 to get correct rounding on division below
		temp >>= 8;										// Divide result to get Kelvin
		uint16_t Kelvin = temp - 4;						// Store the results in variable and extra fine tune

		
		// 2. also from the datasheet page  381, to high value, need some tweaking
		uint16_t temp2 = ((((ADC0.RESH << 8) | ADC0.RESL) - SIGROW.TEMPSENSE1) * SIGROW.TEMPSENSE0) >> 8;
		
		uint16_t Celsius2 = Kelvin - 273;					// Convert Kelvin to Celsius
		uint16_t Fahrenheit  = ((Kelvin - 273) * 1.8) + 32; // Convert Kelvin to Fahrenheit
		
		printf("sig_offset		: %3d\n\r", sigrow_offset);
		printf("sig_gain		: %3d\n\r", sigrow_gain);
		printf("adc_reading		: %3d\n\r", adc_reading);
		printf("Kelvin			: %3d\n\r", Kelvin);	// extra offset to fine tune the results.
		printf("Celsius			: %3d\n\r", Celsius2);
		printf("Fahrenheit		: %3d\n\r", Fahrenheit);
		printf("\n\r");
		printf("temp2			: %3d\n\r", temp2);
		printf("\n\r");
		printf("ADC0 Value :%4d Celsius1 : %3d \n\r",temp_ADC,Celsius1);     // output my own code results.
		_delay_ms(2000);
    }
}

