default:
	avr-gcc -Wall -g2 -Os -mmcu=atmega328p -DF_CPU=12000000UL -MMD -MP -MF"spi.d" -MT"spi.d" -c -o"spi.o" "spi.c"
	avr-ar -r "libspi.a" spi.o
	avr-size --format=avr --mcu=atmega328p libspi.a

clean:
	rm *.hex *.o *.bin *.a *.lss *.d
