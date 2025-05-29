#include <avr/io.h>
#include <stdlib.h>

#define BAUDS 9600UL

void uart_init(uint16_t ubrr)
{
    UBRR0H = (uint16_t)(ubrr >> 8);
	UBRR0L = (uint16_t)ubrr;

    UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Enable Rx and Tx
    UCSR0C = (1<<USBS0) | (3<<UCSZ00); // 8 data bits, 2 stop bits
}

void uart_write_byte(unsigned char data)
{
    while (!(UCSR0A & (1<<UDRE0))) {}; // Wait for UDRE0 to be ready => data available

	UDR0 = data; // Writing the data to be sent
}

void uart_write_str(char *str)
{
    while (*str != '\0')
    {
        uart_write_byte(*str++);
    }
    uart_write_byte('\0');
}

void uart_write_num(int number)
{
	int num_size = 1;

	for (int i = number; i > 1; i /= 10, num_size++);
	char *str_num = malloc(sizeof(char) * (num_size + 1));

	if (str_num == NULL)
	{
		uart_write_str("Malloc failed\n");
		return;
	}

	str_num[num_size] = '\0';
	num_size--;
	while (num_size >= 0)
	{
		str_num[num_size] = number % 10 + '0';
		number = number / 10;
		num_size--;
	}

	uart_write_str(str_num);

	free(str_num);
}
