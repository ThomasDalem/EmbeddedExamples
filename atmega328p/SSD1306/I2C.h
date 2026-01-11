#ifndef MY_I2C_H
#define MY_I2C_H

#include <stdint.h>

#define I2C_MAX_BYTES 32

void i2c_init(void);
void i2c_start(void);
void i2c_address(uint8_t address);
void i2c_send_byte(uint8_t byte);
void i2c_stop(void);
void i2c_send_string(char *str);

#endif