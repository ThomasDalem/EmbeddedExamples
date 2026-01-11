default: lib
	avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000UL -c -o main.o main.c
	avr-gcc -mmcu=atmega328p -o main.bin main.o -li2c -L./
	avr-objcopy -O ihex -j .text -j .data -R .eeprom main.bin main.hex

lib:
	avr-gcc -Wall -g2 -Os -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"I2C_sender.d" -MT"I2C_sender.d" -c -o"I2C_sender.o" "I2C_sender.c"
	avr-ar -r "libi2c.a" I2C_sender.o
	avr-size --format=avr --mcu=atmega328p libi2c.a

flash:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:I2C_sender.hex

clean:
	rm *.hex *.o *.bin *.a *.d

.PHONY: flash lib