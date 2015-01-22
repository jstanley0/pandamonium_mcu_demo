#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// initialize data direction
	// LED is output on bit 3 of PORTB (PB3)
	DDRB = 0b00001000;

	for(;;)
	{
		// turn it on
		PORTB |= (1 << 3);
		_delay_ms(200);

		// turn it off
		PORTB &= ~(1 << 3);
		_delay_ms(200);
	}
}
