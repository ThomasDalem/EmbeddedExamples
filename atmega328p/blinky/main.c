/*
*  Blinky example
*  This code will make the port D8 (Arduino UNO) turn on and off each second
*/

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = DDRB |= (1 << DDB0); // Sets the direction of the port B0 (D8 on an Arduino UNO) to output

    while (1)
    {
        PORTB |= (1 << PORTB0); // Turns the led on by setting the bit PORTB0 on register PORTB to 1
        _delay_ms(1000);
        PORTB &= ~(1 << PORTB0); // Turns the led off by setting it to 0
        _delay_ms(1000);
    }

    return 0;
}
