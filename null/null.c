#include <avr/sleep.h>

int main(void)
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();
}
