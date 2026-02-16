#include <util/delay.h>
#include <avr/io.h>
#include "spi.h"

int main(void)
{
    SPI_init();

    _delay_ms(3000);

    PORTB |= (1 << PORTB2);
    SPI_send(50);

    while (1)
    {

    }
}
