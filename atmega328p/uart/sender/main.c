/*
*  UART example
*  This example send a string via UART to another device
*/

#define F_OSC 16000000UL // Oscillator frequency
#define BAUDS 9600UL
#define UBBR (F_OSC / (16UL * BAUDS)) - 1

#include <avr/io.h>
#include <util/delay.h>

void uart_init()
{
    UBRR0H = UBBR >> 8;
	UBRR0L = UBBR;

    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Enable Rx and Tx
}

void uart_send_byte(char data)
{
    while (( UCSR0A & (1<<UDRE0)) == 0); // Wait for UDRE0 to be ready => data available
	UDR0 = data; // Writing the data to be sent
}

void uart_send_str(char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(*str++);
    }
    uart_send_byte('\0');
}

int main(void)
{
    uart_init();

    while (1)
    {
        uart_send_str("Hello world");
        _delay_ms(1000);
    }
}
