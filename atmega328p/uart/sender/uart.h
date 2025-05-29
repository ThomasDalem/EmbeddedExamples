#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(uint16_t ubrr);
void uart_write_byte(unsigned char data);
void uart_write_str(char *str);
void uart_write_num(int number);

#endif