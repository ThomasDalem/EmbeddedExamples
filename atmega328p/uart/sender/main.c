/*
*  UART example
*  This example send a string via UART to another device
*/

#define F_OSC 16000000UL // Oscillator frequency

#include <avr/io.h>
#include <util/delay.h>

#define BAUDS 9600UL
#define MYUBRR (F_OSC / (16UL * BAUDS)) - 1

void uart_init(uint16_t ubrr)
{
    UBRR0H = (uint16_t)(ubrr >> 8);
	UBRR0L = (uint16_t)ubrr;

    UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Enable Rx and Tx
    UCSR0C = (1<<USBS0) | (3<<UCSZ00); // 8 data bits, 2 stop bits
}

void uart_send_byte(unsigned char data)
{
    while (!(UCSR0A & (1<<UDRE0))); // Wait for UDRE0 to be ready => data available

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
    uart_init(MYUBRR);

    while (1)
    {
        uart_send_str("Hello world");
        _delay_ms(1000);
    }

    return 0;
}
