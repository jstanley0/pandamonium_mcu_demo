#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// initialize data direction
	// LED is output on bit 4 of PORTB (PB4)
	DDRB = 0b00010000;

	for(;;)
	{
		// turn it on
		PORTB |= (1 << 4);
		_delay_ms(100);

		// turn it off
		PORTB &= ~(1 << 4);
		_delay_ms(400);
	}
}
