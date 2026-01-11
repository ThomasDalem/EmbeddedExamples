#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define BAUDS 9600

void i2c_init(void)
{
	TWAR = 0x20; // Address of the slave (receiver)
	TWCR = (1 << TWEA) | (1 << TWEN);
}

void checkData(void)
{
	
}

int main(void)
{
	char buffer[12];

	DDRB = DDRB | (1 << DDB0); // Pin D8 to output mode

    while (1)
    {
		checkData();
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
