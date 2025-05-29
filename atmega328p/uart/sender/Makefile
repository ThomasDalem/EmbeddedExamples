default: lib
	avr-gcc -I./ -Wall -g2 -mmcu=atmega328p -Os -DF_CPU=16000000UL -c -o main.o main.c
	avr-gcc -L./ -mmcu=atmega328p -o main.bin main.o -luart
	avr-objcopy -O ihex -j .text -j .data -R .eeprom main.bin main.hex

lib:
	avr-gcc -Wall -g2 -Os -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"uart.d" -MT"uart.d" -c -o"uart.o" "uart.c"
	avr-ar -r "libuart.a" uart.o
	avr-size --format=avr --mcu=atmega328p libuart.a

flash:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

clean:
	rm *.hex *.o *.bin *.a *.lss *.d
