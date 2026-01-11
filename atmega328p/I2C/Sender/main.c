#include <util/delay.h>

#include "I2C.h"

int main(void)
{
	i2c_init();

	while (1)
	{
		i2c_start();
		i2c_address(0x20);
		i2c_send_string("Hello world");
		i2c_stop();
		_delay_ms(1000);
	}

	return 0;
}
