/*
*  UART example
*  This example receives a string via UART from another device
*/

#define F_OSC 16000000UL // Oscillator frequency

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define BAUDS 9600UL
#define MYUBRR (F_OSC / (16UL * BAUDS)) - 1

void uart_init(uint16_t ubrr)
{
    UBRR0H = (uint16_t)(ubrr >> 8);
	UBRR0L = (uint16_t)ubrr;

    UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Enable Rx and Tx
    UCSR0C = (1<<USBS0) | (3<<UCSZ00); // 8 data bits, 2 stop bits
}

unsigned char uart_get_byte(void)
{
    while (!(UCSR0A & (1<<RXC0))); // Wait for data to be available by checking RXC0

    return UDR0; // Received data is inside UDR0 register
}

void uart_get_str(char *buffer)
{
    int i = 0;
    char c;

    do {
        c = uart_get_byte();
        buffer[i] = c;
        i++;
    } while (c != '\0');
}

void blink_led(unsigned int reg, unsigned int port)
{
    reg |= (1 << port); // Turns the led on by setting the bit PORTB0 on register PORTB to 1
    _delay_ms(1000);
    reg &= ~(1 << port); // Turns the led off by setting it to 0
    _delay_ms(1000);
}

int main(void)
{
    char buffer[20];
    
    DDRB = DDRB |= (1 << DDB0); // Sets the direction of the port B0 (D8 on an Arduino UNO) to output
    
    uart_init(MYUBRR);

    while (1)
    {
        uart_get_str(buffer);
        if (strcmp(buffer, "Hello world") == 0)
        {
            PORTB |= (1 << PORTB0); // Turns the led on by setting the bit PORTB0 on register PORTB to 1
            _delay_ms(500);
            PORTB &= ~(1 << PORTB0); // Turns the led off by setting it to 0
            _delay_ms(500);
        }
    }
}
