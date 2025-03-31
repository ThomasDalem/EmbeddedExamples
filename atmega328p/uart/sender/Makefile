default:
	avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000UL -c -o main.o main.c
	avr-gcc -mmcu=atmega328p -o main.bin main.o
	avr-objcopy -O ihex -j .text -j .data -R .eeprom main.bin main.hex

flash:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

clean:
	rm *.hex *.o *.bin
