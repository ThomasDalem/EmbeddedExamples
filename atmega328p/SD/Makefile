default:
	avr-gcc -I./ -Wall -g2 -mmcu=atmega328p -Os -DF_CPU=12000000UL -c -o main.o main.c
	avr-gcc -L./ -mmcu=atmega328p -o main.bin main.o -lspi
	avr-objcopy -O ihex -j .text -j .data -R .eeprom main.bin main.hex

flash: default
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex

clean:
	rm *.hex *.o *.bin *.a *.lss *.d
