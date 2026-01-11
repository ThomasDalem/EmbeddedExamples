/*
*  OLED 128x64
*  Simple example showing how to display characters on an OLED screen
*/

#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"
#include "SSD1306.h"

void init_screen(void)
{
  SSD1306_send_command(CMD_SET_DISPLAY_OFF);
  SSD1306_send_command(CMD_SET_DISPLAY_CLOCK_DIV);
  SSD1306_send_command(0x80);
  SSD1306_send_command(CMD_SET_MULTIPLEX);
  SSD1306_send_command(64 - 1);
  SSD1306_send_command(CMD_SET_DISPLAY_OFFSET);
  SSD1306_send_command(0x0);
  SSD1306_send_command(CMD_SET_START_LINE | 0x0);
  SSD1306_send_command(CMD_SET_CHARGE_PUMP);
  SSD1306_send_command(0x14);
  SSD1306_send_command(CMD_SET_MEMORY_ADDRESSING_MODE);
  SSD1306_send_command(0x0);
  SSD1306_send_command(CMD_SET_SEGMENT_REMAP_NORMAL | 0x1);
  SSD1306_send_command(CMD_SET_COMSCANDEC);
  SSD1306_send_command(CMD_SET_COMPINS);
  SSD1306_send_command(0x12);
  SSD1306_send_command(CMD_SET_CONTRAST_CONTROL);
  SSD1306_send_command(0xCF);
  SSD1306_send_command(CMD_SET_PRECHARGE);
  SSD1306_send_command(0xF1);
  SSD1306_send_command(CMD_SET_VCOMDETECT);
  SSD1306_send_command(0x40);
  SSD1306_send_command(CMD_SET_ENTIRE_DISPLAY_ON_RESUME);
  SSD1306_send_command(CMD_SET_NORMAL_DISPLAY);
  SSD1306_send_command(CMD_SET_DEACTIVATE_SCROLL);
  SSD1306_send_command(CMD_SET_DISPLAY_ON);
}

int main(void)
{
    i2c_init();

    _delay_ms(1000);

    init_screen();

    SSD1306_draw(0);

    while (1)
    {
        _delay_ms(1000);
    }

    return 0;
}