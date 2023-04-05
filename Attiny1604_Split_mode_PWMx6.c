/*
 * Attiny1604_PWMx6_Split_mode.c
 *
 * Created: 5-4-2023 11:01:40
 * Author : PeetHobby @PeetGaming
 * 
 * Simple example how to initial TCA timer in split mode
 * Have six 8bit outputs with two 8bit period registers that work separately from each other.
 * 
 */ 

#define F_CPU 3333333		//3.3MHz default clock
#include <avr/io.h>
#include <util/delay.h>

 void split_mode_pwm_init(void){
	 // Split mode has up to 6 PWM output
	 PORTA.DIR |= 0b00111000;  //PA3=WO3 PA4=WO4 PA5=WO5
	 PORTB.DIR |= 0b00000111;  //PB0=WO0 PB1=WO1 PB2=WO2
	 
	 // TCA0 Hard reset, set all registers back to the default values
	 TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
	 TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESET_gc;
	 
	 // Enable split mode in CTRLD register.
	 TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;
	 
	 // In split mode timer always counts down, always bottom update.
	 TCA0.SPLIT.CTRLB =	TCA_SPLIT_LCMP0EN_bm |		// Enable  Compare Channel 0
	 			TCA_SPLIT_LCMP1EN_bm |		// Enable  Compare Channel 1
	 			TCA_SPLIT_LCMP2EN_bm |		// Enable  Compare Channel 2
	 			TCA_SPLIT_HCMP0EN_bm |		// Enable  Compare Channel 3
	 			TCA_SPLIT_HCMP1EN_bm |		// Enable  Compare Channel 4
	 			TCA_SPLIT_HCMP2EN_bm;		// Enable  Compare Channel 5

	 // Period is split in two, LPER and HPER, they work independently.
	 TCA0.SPLIT.LPER = 255;		// Set Period for WO0/WO1/WO2 0-255(8bit)
	 TCA0.SPLIT.HPER = 255;		// Set Period for WO3/WO4/WO5
	 
	 // Set initial values of each compare register, 0x00 is default.
	 TCA0.SPLIT.LCMP0 = 10;		// Duty cycle for WO0 PB0 0-255(8bit)
	 TCA0.SPLIT.LCMP1 = 10;		// Duty cycle for WO1 PB1
	 TCA0.SPLIT.LCMP2 = 10;		// Duty cycle for WO2 PB2
	 TCA0.SPLIT.HCMP0 = 10;		// Duty cycle for WO3 PA3
	 TCA0.SPLIT.HCMP1 = 10;		// Duty cycle for WO4 PA4
	 TCA0.SPLIT.HCMP2 = 10;		// Duty cycle for WO5 PA5
	 
	 // Set prescaler to the preferred value and enable timer TCA.
	 TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV256_gc| TCA_SPLIT_ENABLE_bm;
 }


int main(void)
{
	split_mode_pwm_init();
	uint8_t count; 
	
    while (1) 
    {
		// Simple example how to changes the PWM output value for one of the outputs
		// Count will have value between 0-255 and will be stored in LCMP0 so the output WO0 goes form zero to full duty. 
		// This is just one output but you can do that will all six outputs. 
		TCA0.SPLIT.LCMP0 = count;	
		
		count++;
		_delay_ms(50);
		
		if(count > 255) 
			count = 0;
    }
}

