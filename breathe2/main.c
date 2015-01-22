#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum state_t { BREATHE_IN, BREATHE_OUT, WAIT };

ISR(TIMER0_COMPA_vect)
{
	static enum state_t state = BREATHE_IN;
	static uint8_t x = 0;
	
	switch(state)
	{
	case BREATHE_IN:
		if (x == 255)
			state = BREATHE_OUT;
		else
			x++;
		OCR1B = x;
		break;
	case BREATHE_OUT:
		if (x == 0)
			state = WAIT;
		else
			x--;
		OCR1B = x;
		break;
	case WAIT:
		if (x == 100) {
			x = 0;
			state = BREATHE_IN;
		} else {
			x++;
		}
		break;	
	}
}

int main(void)
{
	// initialize data direction
	// LED is output on bit 4 of PORTB (PB4) / OC1A
	DDRB = 0b00010000;

	// initialize timer0: I want an interrupt every 5ms
	TCCR0A = (1 << WGM01);                  // CTC mode
	TCCR0B = (1 << CS01) | (1 << CS00);	    // 1/64 prescaler; ticks every 64us
	OCR0A = 78;								// 78 * 64us ~= 5ms
	TIMSK = (1 << OCIE0A);	// enable timer0 compare-match A interrupt

	// initialize timer1	
    GTCCR = (1 << PWM1B) | (1 << COM1B1); // PWM mode, clear on compare match
    TCCR1 = (1 << CS12) | (1 << CS11);    // 1/32 prescaler (122 Hz refresh @ 1MHz CPU)
	OCR1B = 0;		// initial brightness
	OCR1C = 255;	// maximum brightness

	// enable interrupts
	sei();

	// main loop does nothing; code is interrupt-driven
	// interrupts wake the processor from sleep mode
	set_sleep_mode(SLEEP_MODE_IDLE);
	for(;;)
	{
		sleep_mode();
	}
}
