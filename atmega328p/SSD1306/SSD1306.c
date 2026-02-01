#include <string.h>
#include <stdlib.h>
#include "SSD1306.h"
#include "I2C.h"

int SSD1306_init_screen(screen_t *screen, uint8_t width, uint8_t height, uint8_t address)
{
    const uint16_t bufSize = screen->width * ((screen->height) / 8);
    screen->buffer = malloc(sizeof(char) * bufSize);

    if (screen->buffer == NULL)
    {
        return ERR;
    }

    memset(screen->buffer, 0, bufSize);

    screen->width = width;
    screen->height = height;
    screen->address = address;

    return OK;
}

void SSD1306_send_command(uint8_t address, uint8_t command)
{
    i2c_start();
    i2c_address(address);
    i2c_send_byte(0x00);
    i2c_send_byte(command);
    i2c_stop();
}

void SSD1306_send_command_list(uint8_t address, uint8_t *commands, uint8_t len)
{
    uint16_t nb_commands_sent = 1;

    i2c_start();
    i2c_send_byte(0x00);

    while (len > 0)
    {
        if (nb_commands_sent > I2C_MAX_BYTES)
        {
            i2c_stop();
            i2c_start();
            i2c_address(address);
            i2c_send_byte(0x00);
            nb_commands_sent = 1;
        }
        i2c_send_byte(*commands++);
        nb_commands_sent++;
    }
    i2c_stop();
}

void SSD1306_set_pixel(screen_t *screen, int x, int y)
{
    screen->buffer[x + (screen->width * (y / 8))] |= (1 << (y % 8));
}

void SSD1306_fill(screen_t *screen, uint8_t byte)
{
    memset(screen->buffer, byte, screen->width * ((screen->height + 7) / 8));
}

void SSD1306_clear(screen_t *screen)
{
    memset(screen->buffer, 0, screen->width * ((screen->height + 7) / 8));
}

void SSD1306_display(screen_t *screen)
{
    uint16_t bytesOut = 7;

    i2c_start();
    i2c_address(screen->address);

    /* i2c_send_byte(CMD_SET_PAGE_ADDRESS);
    i2c_send_byte(0);
    i2c_send_byte(8 - 1);
    i2c_send_byte(CMD_SET_COLUMN_ADDRESS);
    i2c_send_byte(0);
    i2c_send_byte(128 - 1); */

    i2c_send_byte(0x40);

    for (uint32_t i = 0; i < screen->width * ((screen->height) / 8); i++)
    {
        if (bytesOut >= I2C_MAX_BYTES)
        {
            i2c_stop();
            i2c_start();
            i2c_address(screen->address);
            i2c_send_byte(0x40);
            bytesOut = 1;
        }
        i2c_send_byte(screen->buffer[i]);
        bytesOut++;
    }
    
    i2c_stop();
}
