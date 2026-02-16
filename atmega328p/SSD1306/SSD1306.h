#ifndef SSD1306_H
#define SSD1306_H

#include "stdint.h"

#define CMD_SET_CONTRAST_CONTROL 0x81
#define CMD_SET_ENTIRE_DISPLAY_ON_RESUME 0xA4
#define CMD_SET_ENTIRE_DISPLAY_ON 0xA5
#define CMD_SET_NORMAL_DISPLAY 0xA6
#define CMD_SET_INVERSE_DISPLAY 0xA7
#define CMD_SET_DISPLAY_OFF 0xAE
#define CMD_SET_DISPLAY_ON 0xAF
// Memory addresing
#define CMD_SET_MEMORY_ADDRESSING_MODE 0x20
#define CMD_SET_MEMORY_ADDRESSING_MODE_HORIZONTAL 0x00
#define CMD_SET_MEMORY_ADDRESSING_MODE_VERTICAL 0x01
#define CMD_SET_MEMORY_ADDRESSING_MODE_PAGE 0x02
#define CMD_SET_COLUMN_ADDRESS 0x21
#define CMD_SET_PAGE_ADDRESS 0x22
#define CMD_SET_SEGMENT_REMAP_NORMAL 0xA0
#define CMD_SET_SEGMENT_REMAP_INVERTED 0xA1
#define CMD_SET_CLOCK_OSCILLATOR 0xD5
#define CMD_SET_START_LINE 0x40
#define CMD_SET_DISPLAY_CLOCK_DIV 0xD5
#define CMD_SET_MULTIPLEX 0xA8
#define CMD_SET_DISPLAY_OFFSET 0xD3
#define CMD_SET_CHARGE_PUMP 0x8D
#define CMD_SET_COMSCANDEC 0xC8
#define CMD_SET_COMSCANINC 0xC0
#define CMD_SET_COMPINS 0xDA
#define CMD_SET_PRECHARGE 0xD9
#define CMD_SET_VCOMDETECT 0xDB
#define CMD_SET_DEACTIVATE_SCROLL 0x2E

#define SLA 0x3C
#define WIDTH 128
#define HEIGHT 64

#define OK 0
#define ERR 1

#define WIDTH 128
#define HEIGHT 64
#define BUFFER_SIZE WIDTH * (HEIGHT / 8)

typedef struct screen_s
{
    char buffer[BUFFER_SIZE];
    uint8_t address;
} screen_t;

typedef struct pos_s
{
    uint8_t x;
    uint8_t y;
} pos_t;

void SSD1306_init_screen(screen_t *screen, uint8_t address);
void SSD1306_send_command(uint8_t address, uint8_t command);
void SSD1306_send_command_list(uint8_t address, uint8_t *commands, uint8_t len);
void SSD1306_fill(screen_t *screen, uint8_t byte);
void SSD1306_draw_pixel(screen_t *screen, int x, int y);
void SSD1306_draw_line(screen_t *screen, const pos_t *p1, const pos_t *p2);
void SSD1306_clear(screen_t *screen);
/**
 * Sends the buffer to the screen.
 * @param screen pointer to the screen structure containing the buffer
 */
void SSD1306_display(screen_t *screen);

#endif