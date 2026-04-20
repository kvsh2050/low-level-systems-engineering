MCU     = atmega328p
F_CPU   = 16000000UL
PORT    = /dev/ttyACM0
BAUD    = 115200
CC      = avr-gcc
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
BOARD	= arduino

all: blink.hex
.PHONY: compile_asm 

blink.elf: main.c
	$(CC) $(CFLAGS) -o blink.elf main.c

blink.hex: blink.elf
	avr-objcopy -O ihex blink.elf blink.hex

flash: blink.hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:blink.hex

clean:
	rm -f blink.elf blink.hex

compile_asm: blink_asm.S 
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -x assembler-with-cpp -o main.elf blink_asm.S
	avr-objcopy -O ihex main.elf main.hex
	avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex
