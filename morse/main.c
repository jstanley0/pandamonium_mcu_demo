#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <ctype.h>

#define DOT_MILLISECONDS 100

// use constants here
#define delay(dots) _delay_ms((dots)*DOT_MILLISECONDS)

// international morse code table, from ' ' (32) to '_' (95)
// 0 = symbol is not defined; treated as a space here
// otherwise, the highest 1 bit marks the size of the code
// and the remaining bits give the symbol (dot = 0; dash = 1)
// in left-to-right, MSB-to-LSB order
static const uint8_t morse_table[64] PROGMEM = {
	0,          //  
	0b1101011,  // !
	0b1010010,  // "
	0,          // #
	0b10001001, // $
	0,          // %
	0b101000,   // &
	0b1011110,  // '
	0b110110,   // (
	0b1101101,  // )
	0,          // *
	0b101010,   // +
	0b1110011,  // ,
	0b1100001,  // -
	0b1010101,  // .
	0b110010,   // /
	0b111111,   // 0
	0b101111,   // 1
	0b100111,   // 2
	0b100011,   // 3
	0b100001,   // 4
	0b100000,   // 5
	0b110000,   // 6
	0b111000,   // 7
	0b111100,   // 8
	0b111110,   // 9
	0b1111000,  // :
	0b1101010,  // ;
	0,          // <
	0b110001,   // =
	0,          // >
	0b1001100,  // ?
	0b1011010,  // @
	0b101,      // A
	0b11000,    // B
	0b11010,    // C
	0b1100,     // D
	0b10,       // E
	0b10010,    // F
	0b1110,     // G
	0b10000,    // H
	0b100,      // I
	0b10111,    // J
	0b1101,     // K
	0b10100,    // L
	0b111,      // M
	0b110,      // N
	0b1111,     // O
	0b10110,    // P
	0b11101,    // Q
	0b1010,     // R
	0b1000,     // S
	0b11,       // T
	0b1001,     // U
	0b10001,    // V
	0b1011,     // W
	0b11001,    // X
	0b11011,    // Y
	0b11100,    // Z
	0,          // [
	0,          // '\'
	0,          // ]
	0,          // ^
	0b1001101   // _
};

void init_io()
{
	DDRB = 0b00010000;
	PORTB = 0;
}

inline void led_on()
{
	PORTB |= (1 << 4);
}

inline void led_off()
{
	PORTB &= ~(1 << 4);
}

void write_symbol(uint8_t sym)
{
	if (sym == 0)
	{
		delay(7);	// space
	}
	else
	{
		uint8_t bit = 0x80;
		while((sym & bit) == 0)
			bit >>= 1;
		bit >>= 1;
		while(bit != 0)
		{
			led_on();
			if (sym & bit)
				delay(3);	// dash
			else
				delay(1);	// dot
			led_off();
			delay(1);
			bit >>= 1;
		}
		delay(2);
	}
}

void write_string(const char *str)
{
	const char *p = str;
	char ch;
	while(ch = *p++)
	{
		ch = toupper(ch);
		if (ch < ' ' || ch > '_')
			ch = ' ';
		write_symbol(pgm_read_byte(&morse_table[ch - ' ']));
	}
}

int main(void)
{
	init_io();

	for(;;)
	{
		write_string("Hello World! Welcome to Pandamonium.");
	}
}
