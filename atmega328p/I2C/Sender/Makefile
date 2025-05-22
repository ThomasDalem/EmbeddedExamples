default:
	avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000UL -c -o I2C_sender.o I2C_sender.c
	avr-gcc -mmcu=atmega328p -o I2C_sender.bin I2C_sender.o
	avr-objcopy -O ihex -j .text -j .data -R .eeprom I2C_sender.bin I2C_sender.hex

.PHONY: deploy
deploy:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:I2C_sender.hex