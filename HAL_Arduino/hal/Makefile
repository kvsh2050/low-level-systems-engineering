# --- Project Configuration ---
# Match these to your hardware and HAL settings
MCU          = atmega328p
F_CPU        = 16000000UL
BAUD         = 115200
PORT         = /dev/ttyACM0
PROGRAMMER   = arduino

# --- Tools ---
CC           = avr-gcc
OBJCOPY      = avr-objcopy
AVRDUDE      = avrdude

# --- Compiler Flags ---
# -Os: Optimize for size (Professional standard for embedded)
# -Wall: Show all warnings (Crucial for debugging)
CFLAGS       = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# --- Files ---
TARGET       = app
SRCS         = app.c
# If you have separate .c files for logic, add them here:
# SRCS       = main.c UART.c Timer.c

# --- DIRECTORY ---

# --- Build Rules ---

all: $(TARGET).hex

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET).elf

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

# The "Flash" command
flash: $(TARGET).hex
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -D -U flash:w:$(TARGET).hex:i

# Clean up the folder
clean:
	rm -f $(TARGET).elf $(TARGET).hex