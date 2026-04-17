MCU     = atmega328p
F_CPU   = 16000000UL
PORT    = /dev/ttyACM0
BAUD    = 115200
CC      = avr-gcc
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
BOARD	= arduino

all: uart.hex
.PHONY: compile_asm 

uart.elf: uart_app.c
	$(CC) $(CFLAGS) -o uart.elf uart_app.c usart0.c

uart.hex: uart.elf
	avr-objcopy -O ihex uart.elf uart.hex

flash: uart.hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:uart.hex

clean:
	rm -f uart.elf uart.hex

compile_asm: blink_asm.S 
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -x assembler-with-cpp -o uart.elf uart.S
