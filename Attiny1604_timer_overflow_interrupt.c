/*
 * Timer overflow interrupt.c
 *
 * Created: 25-1-2023 17:31:48
 * Author : PeetHobby @PeetGaming
 *
 * For more information see: TB3217 - Getting Started with TCA
 * 
 * This is a simple example of TCA timer overflow interrupt(TCA0_OVF_vect)
 *
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void init_interrupt(void);
void GPIO_init(void);
inline void toggle_led(void);

int main(void)
{
	init_interrupt();
	GPIO_init();
	toggle_led();
	
	while (1)
	{
	}
}

void GPIO_init(void){
	
	PORTB.OUT |= PIN2_bm;
	PORTB.DIR |= PIN2_bm;
}

void init_interrupt(void) {
	// Setting the corresponding bit in the Interrupt Control register enables the overflow interrupt of TCA.
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	
	//In this mode, no waveform must be generated.
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	
	TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);
	
	TCA0.SINGLE.PER = 0x0CB6;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc	| TCA_SINGLE_ENABLE_bm;

	// Enable global interrupts
	sei();
}

inline void toggle_led(void)
{
	PORTB.OUTTGL |= PIN2_bm;
}

ISR(TCA0_OVF_vect)
{
	toggle_led();
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
