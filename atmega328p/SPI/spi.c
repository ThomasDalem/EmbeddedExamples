#include <avr/io.h>
#include "spi.h"

#define SS DDB2
#define MOSI DDB3
#define MISO DDB4
#define CLK DDB5

void SPI_init(void)
{
    DDRB = (1<<MOSI) | (1<<CLK) | (1<<SS);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

unsigned char SPI_send(unsigned char data)
{
    SPDR = data;

    while(!(SPSR & (1<<SPIF)));

    return SPDR;
}

void SPI_send_str(const char *str)
{
    while (*str != '\0')
    {
        SPI_send(*str++);
    }
}