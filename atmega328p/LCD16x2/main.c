/*
*  LCD 16x2
*  Simple example showing how to display characters on an LCD (Hitachi HD44780 or JHD162A)
*/

#include <avr/io.h>
#include <util/delay.h>

// Screen clear Command
#define SCREEN_CLEAR 0x01

// Cursor return command
#define CURSOR_RETURN 0x02

// Input set command
#define INCREMENT_MODE 0x06
#define DECREMENT_MODE 0x04
#define SHIFT 0x05
#define NO_SHIFT 0x04

// Display switch command
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CURSOR_ON 0x0A
#define CURSOR_OFF 0x08
#define BLINK_ON 0x09
#define BLINK_OFF 0x08

// Shift command
#define DISPLAY_SHIFT 0x18
#define CURSOR_SHIFT 0x10
#define RIGHT_SHIFT 0x14
#define LEFT_SHIFT 0x10

// Function set command
#define DATA_LENGTH_8 0x30
#define DATA_LENGTH_4 0x20
#define TWO_ROWS 0x28
#define ONE_ROW 0x20
#define STYLE_5X10 0x24
#define STYLE_5X8 0x20


#define RS_PORT PORTD2
#define RW_PORT PORTD3
#define EN_PORT PORTD4

#define DB4 PORTB0
#define DB5 PORTB1
#define DB6 PORTB2
#define DB7 PORTB3

void send_command(char command)
{
    char upper_half = command >> 4;
    char lower_half = command & 0x0F;

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

void send_enable_signal()
{
    PORTD |= (1 << EN_PORT);
    _delay_ms(1);
    PORTD &= ~(1 << EN_PORT);
    _delay_ms(1);
}

void send_init_command(char c)
{
    const char command = c & 0x0F;

    PORTD |= (1 << RS_PORT);
    PORTD &= ~(1 << RW_PORT);
    PORTB &= 0xF0; // Reset the beginning of PORTB
    PORTB |= command;
    send_enable_signal();
}

void init_lcd()
{
    _delay_ms(20);

    send_init_command(0x03);
    _delay_ms(5);
    send_init_command(0x03);
    _delay_ms(1);
    send_init_command(0x03);
    _delay_ms(1);
    send_init_command(0x02);

    _delay_ms(500);

    send_command(DATA_LENGTH_4 | TWO_ROWS | STYLE_5X8);
    send_command(DISPLAY_ON | CURSOR_ON | BLINK_ON);
    send_command(SCREEN_CLEAR);
    send_command(INCREMENT_MODE | NO_SHIFT);
}

int main(void)
{
    // Set direction of ports to OUTPUT
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
    DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4);

    _delay_ms(15); // Wait for LCD to initialize (min 15ms)

    init_lcd();

    _delay_ms(100); // Wait for LCD to initialize (min 15ms)

    print_string("Hello world");

    while (1)
    {
        //_delay_ms(5000);
    }

    return 0;
}