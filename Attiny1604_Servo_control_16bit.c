/*
 * Attiny1604_3x_Servo_control_16bit.c
 *
 * Created: 7-4-2023 15:01:20
 * Author : PeetHobby @PeetGaming
 */ 

#define F_CPU 20000000 // F_CPU is also declared in uart_printf.c
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Clock_20Mhz_init() {
	ccp_write_io((void*) &(CLKCTRL.MCLKCTRLA), CLKCTRL_CLKSEL_OSC20M_gc);	// 20MHz Internal Oscillator
	ccp_write_io((void*) &(CLKCTRL.MCLKCTRLB), ~CLKCTRL_PEN_bm);			// Enable clock system
}

void Servo_16bit_PWM_init(void){
	
	// SingleSlope(normal mode) has up to three 16bit PWM signals
	PORTB.DIR |= 0b00000111;  //PB0=WO0 PB1=WO1 PB2=WO2
	
	// TCA0 Hard reset, set all registers back to the default values
	TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
	TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESET_gc;
	
	// Enable PWM channels, comment out what you don't need
	TCA0.SINGLE.CTRLB |=  TCA_SINGLE_CMP0EN_bm;		// Enable WMO0 PB1
	//TCA0.SINGLE.CTRLB |=  TCA_SINGLE_CMP1EN_bm;	// Enable WMO1 PB2
	//TCA0.SINGLE.CTRLB |=  TCA_SINGLE_CMP2EN_bm;	// Enable WMO2 PB3
	
	TCA0.SINGLE.CTRLB |=  TCA_SINGLE_WGMODE_SINGLESLOPE_gc;	// Set the waveform generator to single slope
	TCA0.SINGLE.PER = 0xffff;	// Set Period (16bit 0-65535)
	
	// Set default initial compare register values
	TCA0.SINGLE.CMP0 = 0;		// Duty cycle for WO0 PB0 (16bit 0-65535)
	TCA0.SINGLE.CMP1 = 0;		// Duty cycle for WO1 PB1
	TCA0.SINGLE.CMP2 = 0;		// Duty cycle for WO2 PB2

	// Set prescaler to the preferred value and enable timer TCA.
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc | TCA_SINGLE_ENABLE_bm;
}

void servo_pos(uint32_t angle){
	uint32_t pulse_us = 1000 + (angle * 1000 / 180);	// convert the angle to pulse width in microseconds, between 1000-2000us
	uint32_t timer_counts = (pulse_us  - 600) * 3.75;	// convert the pulse width to timer counts value, offset(-600 in my case) to 1ms and multply to increase the value. 
	TCA0.SINGLE.CMP0 = timer_counts;					// set timer1 compare register with the calculated counts value
}

int main(void)
{
	Clock_20Mhz_init();
    Servo_16bit_PWM_init();
	
    while (1) 
    {
		// Simple Servo Test 
		servo_pos(0);
		_delay_ms(1000);
		servo_pos(90);
		_delay_ms(1000);
		servo_pos(180);
		_delay_ms(1000);
    }
}

