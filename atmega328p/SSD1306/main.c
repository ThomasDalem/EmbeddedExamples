/*
*  OLED 128x64
*  Simple example showing how to display characters on an OLED screen
*/

#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"
#include "SSD1306.h"

void init_screen(uint8_t address)
{
    SSD1306_send_command(address, CMD_SET_DISPLAY_OFF);
    SSD1306_send_command(address, CMD_SET_CONTRAST_CONTROL);
    SSD1306_send_command(address, 0x7F);
    SSD1306_send_command(address, CMD_SET_NORMAL_DISPLAY);
    SSD1306_send_command(address, CMD_SET_DEACTIVATE_SCROLL);
    SSD1306_send_command(address, CMD_SET_MEMORY_ADDRESSING_MODE);
    SSD1306_send_command(address, CMD_SET_MEMORY_ADDRESSING_MODE_HORIZONTAL);
    SSD1306_send_command(address, CMD_SET_SEGMENT_REMAP_NORMAL | 0x1);
    SSD1306_send_command(address, CMD_SET_MULTIPLEX);
    SSD1306_send_command(address, 64 - 1);
    SSD1306_send_command(address, CMD_SET_COMSCANDEC);
    SSD1306_send_command(address, CMD_SET_DISPLAY_OFFSET);
    SSD1306_send_command(address, 0x00);
    SSD1306_send_command(address, CMD_SET_COMPINS);
    SSD1306_send_command(address, 0x12);
    SSD1306_send_command(address, CMD_SET_DISPLAY_CLOCK_DIV);
    SSD1306_send_command(address, 0x80);
    SSD1306_send_command(address, CMD_SET_PRECHARGE);
    SSD1306_send_command(address, 0x22);
    SSD1306_send_command(address, CMD_SET_VCOMDETECT);
    SSD1306_send_command(address, 0x20);
    SSD1306_send_command(address, CMD_SET_CHARGE_PUMP);
    SSD1306_send_command(address, 0x14);
    SSD1306_send_command(address, CMD_SET_DISPLAY_OFFSET);
    SSD1306_send_command(address, 0x00);
    SSD1306_send_command(address, CMD_SET_ENTIRE_DISPLAY_ON_RESUME);
    SSD1306_send_command(address, CMD_SET_DISPLAY_ON);
}

int main(void)
{
    screen_t screen;

    i2c_init();

    SSD1306_init_screen(&screen, 0x3C);
    init_screen(screen.address);

    _delay_ms(500);

    SSD1306_clear(&screen);
    SSD1306_display(&screen);

    for (int x = 30, y = 20; x < 40; x++, y++)
    {
        SSD1306_draw_pixel(&screen, x, y);
    }
    for (int x = 40, y = 20; x > 30; x--, y++)
    {
        SSD1306_draw_pixel(&screen, x, y);
    }
    SSD1306_draw_pixel(&screen, 127, 63);

    pos_t p1 = {5, 5};
    pos_t p2 = {25, 10};
    SSD1306_draw_line(&screen, &p1, &p2);

    SSD1306_display(&screen);

    while (1)
    {
        _delay_ms(1000);
    }

    return 0;
}
