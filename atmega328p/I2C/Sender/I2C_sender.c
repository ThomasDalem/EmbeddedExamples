#include <avr/io.h>
#include <stdint.h>

#define SCL_CLOCK 50000L // 50 kHz
#define F_CPU 16000000UL

void i2c_init(void)
{
  	TWSR = 0;
  	TWBR = ((F_CPU / SCL_CLOCK) - 16 ) / 2;

  	TWCR = (1 << TWEN) | (1 << TWEA);
}

void i2c_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
}

void i2c_address(uint8_t address)
{
	TWDR = (address << 1); // Address is 7 bits + 1 R/W bit (0 = write, 1 = read)
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
}

void i2c_send_byte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void i2c_send_string(char *str)
{
	while (*str != '\0')
	{
		i2c_send_byte(*str);
		str++;
	}
}
