default: lib
	avr-gcc -I./ -Wall -g2 -mmcu=atmega328p -Os -DF_CPU=16000000UL -c -o main.o main.c
	avr-gcc -L./ -mmcu=atmega328p -o main.bin main.o -lssd1306 -L./ -li2c -L../I2C/Sender
	avr-objcopy -O ihex -j .text -j .data -R .eeprom main.bin main.hex

lib:
	avr-gcc -Wall -g2 -Os -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"SSD1306.d" -MT"SSD1306.d" -c -o"SSD1306.o" "SSD1306.c"
	avr-ar -r "libssd1306.a" SSD1306.o
	avr-size --format=avr --mcu=atmega328p libssd1306.a

flash: default
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex

clean:
	rm *.hex *.o *.bin *.a *.lss *.d
