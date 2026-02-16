#include <string.h>
#include <stdlib.h>
#include "SSD1306.h"
#include "I2C.h"

void SSD1306_init_screen(screen_t *screen, uint8_t address)
{
    memset(screen->buffer, 0, BUFFER_SIZE);

    screen->address = address;
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

void SSD1306_draw_pixel(screen_t *screen, int x, int y)
{
    screen->buffer[x + (WIDTH * (y / 8))] |= (1 << (y % 8));
}

void SSD1306_draw_line(screen_t *screen, const pos_t *p1, const pos_t *p2)
{
    int m_new = 2 * (p2->y - p1->y);
    int slope_error_new = m_new - (p2->x - p1->x);
    for (int x = p1->x, y = p1->y; x <= p2->x; x++) {
        SSD1306_draw_pixel(screen, x, y);

        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0) {
            y++;
            slope_error_new -= 2 * (p2->x - p1->x);
        }
    }
}

void SSD1306_fill(screen_t *screen, uint8_t byte)
{
    memset(screen->buffer, byte, WIDTH * ((HEIGHT) / 8));
}

void SSD1306_clear(screen_t *screen)
{
    memset(screen->buffer, 0, WIDTH * ((HEIGHT) / 8));
}

void SSD1306_display(screen_t *screen)
{
    uint16_t bytesOut = 7;

    i2c_start();
    i2c_address(screen->address);

    i2c_send_byte(0x40);

    for (uint32_t i = 0; i < WIDTH * ((HEIGHT) / 8); i++)
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
