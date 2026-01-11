/*
*  LCD 16x2
*  Simple example showing how to display characters on an LCD (Hitachi HD44780 or JHD162A)
*/

#include <avr/io.h>
#include <util/delay.h>

#define RS_PORT PORTD2
#define RW_PORT PORTD3
#define EN_PORT PORTD4

#define DB4 PORTB0
#define DB5 PORTB1
#define DB6 PORTB2
#define DB7 PORTB3

void send_command(char command)
{
    const char upper_half = command >> 4;
    const char lower_half = command & 0x0F;

    PORTD &= ~(1 << RS_PORT);
    PORTD &= ~(1 << RW_PORT);
    PORTB &= 0xF0;
    PORTB |= upper_half;
    PORTD |= (1 << EN_PORT);
    _delay_ms(5);
    PORTD &= ~(1 << EN_PORT);
    _delay_ms(5);

    PORTB &= 0xF0;
    PORTB |= lower_half;
    PORTD |= (1 << EN_PORT);
    _delay_ms(5);
    PORTD &= ~(1 << EN_PORT);
    _delay_ms(5);
}

void print_letter(char c)
{
    const char upper_half = c >> 4;
    const char lower_half = c & 0x0F;

    PORTD |= (1 << RS_PORT);
    PORTD &= ~(1 << RW_PORT);
    PORTB &= 0xF0; // Reset the beginning of PORTB
    PORTB |= upper_half;
    PORTD |= (1 << EN_PORT);
    _delay_ms(1);
    PORTD &= ~(1 << EN_PORT);
    _delay_ms(1);

    PORTB &= 0xF0;
    PORTB |= lower_half; // Reset the beginning of PORTB
    PORTD |= (1 << EN_PORT);
    _delay_ms(1);
    PORTD &= ~(1 << EN_PORT);
    _delay_ms(1);
}

void print_string(const char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        print_letter(str[i]);
        i++;
    }
}

void init_lcd(void)
{
    _delay_ms(15);

    send_command(0x28);
    send_command(0x0F);
    send_command(0x01);
    send_command(0x06);
}

int main(void)
{
    // Set direction of ports to OUTPUT
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
    DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4);

    _delay_ms(15); // Wait for LCD to initialize (min 15ms)

    init_lcd();

    print_string("Test");

    while (1)
    {
        //_delay_ms(5000);
    }

    return 0;
}