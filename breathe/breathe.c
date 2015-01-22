#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// initialize data direction
	// LED is output on bit 4 of PORTB (PB4) / OC1A
	DDRB = 0b00010000;

	// initialize timer1	
    GTCCR = (1 << PWM1B) | (1 << COM1B1); // PWM mode, clear on compare match
    TCCR1 = (1 << CS12) | (1 << CS11);    // 1/32 prescaler (122 Hz refresh @ 1MHz CPU)
	OCR1B = 0;		// initial brightness
	OCR1C = 255;	// maximum brightness

	for(;;)
	{
		uint8_t bright;
		
		// breathe in
		for(bright = 0; bright < 255; ++bright) {
			OCR1B = bright;
			_delay_ms(5);
		}
		
		// breathe out
		for(; bright > 0; --bright) {
			OCR1B = bright;
			_delay_ms(5);
		}
		
		// wait
		OCR1B = 0;
		_delay_ms(500);
	}
}
