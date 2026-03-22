MCU     = atmega328p
F_CPU   = 16000000UL
PORT    = /dev/ttyACM0
BAUD    = 115200
CC      = avr-gcc
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

all: blink.hex

blink.elf: blink.c
	$(CC) $(CFLAGS) -o blink.elf blink.c

blink.hex: blink.elf
	avr-objcopy -O ihex blink.elf blink.hex

flash: blink.hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:blink.hex

clean:
	rm -f blink.elf blink.hex