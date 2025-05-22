#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define BAUDS 9600

int main(void)
{
	char buffer[12];

	DDRB = DDRB | (1 << DDB0); // Pin D8 to output mode

    while (1)
    {
		if (strcmp(buffer, "Hello world") == 0)
		{
			PORTB = PORTB | (1 << PORTB0);
			_delay_ms(500);
			PORTB = PORTB &~ (1 << PORTB0);
			_delay_ms(300);
		}
    }

	return 0;
}
