/*
*  UART example
*  This example send a string via UART to another device
*/

#define F_OSC 16000000UL // Oscillator frequency

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define BAUDS 9600UL
#define MYUBRR (F_OSC / (16UL * BAUDS)) - 1

int main(void)
{
    uart_init(MYUBRR);

    while (1)
    {
        uart_write_str("Hello world\n");
        _delay_ms(1000);
    }

    return 0;
}
