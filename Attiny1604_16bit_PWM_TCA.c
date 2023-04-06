/*
 * Attiny1604_16bit_PWM_TCA.c
 *
 * Created: 6-4-2023 10:30:20
 * Author : PeetHobby @PeetGaming
 *
 * TCA 3 x 16bit PWM example code
 *
 */ 

#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <util/delay.h>

void PWM_16bit_SingleSlope_init(void){
	
	// SingleSlope(normal mode) has up to three 16bit PWM signals
	PORTB.DIR |= 0b00000111;  //PB0=WO0 PB1=WO1 PB2=WO2
	
	// TCA0 Hard reset, set all registers back to the default values
	TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
	TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESET_gc;

	// Enable WMO0=PB0 WMO1=PB1 WMO2=PB2
	TCA0.SINGLE.CTRLB =  TCA_SINGLE_CMP0EN_bm |			// Enable WMO0 PB1
						 TCA_SINGLE_CMP1EN_bm |			// Enable WMO1 PB2
						 TCA_SINGLE_CMP2EN_bm |			// Enable WMO2 PB3
						 TCA_SINGLE_WGMODE_SINGLESLOPE_gc;	// Set the waveform generator to single slope
	
	TCA0.SINGLE.CNT = 0xffff;	// Set Count (16bit 0-65535)
	TCA0.SINGLE.PER = 0xffff;	// Set Period (16bit 0-65535)
	
	// Set default initial compare register values
	TCA0.SINGLE.CMP0 = 0;		// Duty cycle for WO0 PB0 (16bit 0-65535)
	TCA0.SINGLE.CMP1 = 0;		// Duty cycle for WO1 PB1
	TCA0.SINGLE.CMP2 = 0;		// Duty cycle for WO2 PB2

	// Set prescaler to the preferred value and enable timer TCA.
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;	
}

// Main code
int main(void)
{
	PWM_16bit_SingleSlope_init();
	uint16_t count; 
	
    while (1) 
    {
		// Simple example how to changes the PWM output value for one of the outputs
		// Count will have value between 0-65535 and will be stored in LCMP0 so the output WO0 goes form zero to full duty.
		// This is just one output but you can do that will all six outputs.
		TCA0.SINGLE.CMP0 = count;
				
		count++;
		_delay_us(100); // short delay, 65535 x 100us = 6.5535 seconds
				
		if(count > 65535)
		count = 0;
    }
}

