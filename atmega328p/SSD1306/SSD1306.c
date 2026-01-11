#include "SSD1306.h"
#include "I2C.h"

void SSD1306_send_command(uint8_t command)
{
    i2c_start();
    i2c_address(SLA);
    i2c_send_byte(0x00);
    i2c_send_byte(command);
    i2c_stop();
}

void SSD1306_send_command_list(uint8_t *commands, uint8_t len)
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
            i2c_address(SLA);
            i2c_send_byte(0x00);
            nb_commands_sent = 1;
        }
        i2c_send_byte(*commands++);
    }
    i2c_stop();
}

void SSD1306_draw(char *buffer)
{
    uint16_t count = WIDTH * ((HEIGHT + 8) / 8);
    uint16_t bytesOut = 7;

    i2c_start();
    i2c_address(SLA);

    i2c_send_byte(CMD_SET_PAGE_ADDRESS);
    i2c_send_byte(0);
    i2c_send_byte(8 - 1);
    i2c_send_byte(CMD_SET_COLUMN_ADDRESS);
    i2c_send_byte(0);
    i2c_send_byte(128 - 1);

    i2c_send_byte((uint8_t)0x40);

    while (count--)
    {
        if (bytesOut >= I2C_MAX_BYTES)
        {
            i2c_stop();
            i2c_start();
            i2c_address(SLA);
            i2c_send_byte((uint8_t)0x40);
            bytesOut = 1;
        }
        i2c_send_byte(0xF0);
        bytesOut++;
    }
    
    i2c_stop();
}
