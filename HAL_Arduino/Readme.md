# Harry Potter Arduino Magic

Use harry potter spells to program your Arduino Projects !!!

---

## Programming 

1. For blinking led in the arduino(Go to avr_code_tests/blink_led), use the make file to compile the baremetal code into .elf file and then convert to .hex and make flash to flash it into the board 
<img src="pictures/Image-led-blink.jpeg" alt="Image-led-blink" width="500">


## For Compilation 
1. avr compiler to convert the .c to .hex or .bin 
```
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o blink.elf example.c
```
2. Convert to .hex
```
avr-objcopy -O ihex blink.elf blink.hex
```

## For Flashing
```
avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:blink.hex
```
or 
```
make flash
```

## For serial monitor 
In linux(ubuntu) check these:
1. Find the port name on which the Arduino is connected to 
```
lsusb 
```
2. Find the port in the /dev/* and check for the port on it
```
ls /dev/ttyACM0
```
3. Connect to arduino using picocom 
```
picocom /dev/ttyACM0 -b 115200
```
4. The picocom prints serial messages 


## Repo Structure 

1. code/ : Has code in c and asm wihtout using ardunio library 
2. hal/ : Has code for HAL for the Arduino that you can use in your projects wihtout depending on the Arduino HAL
3. hal_hogwarts/ : Harry potter spell themed HAL

## Harry Potter Spell Mappings
| Spell Name | Technical Function | Real-World Hardware Action |
| :--- | :--- | :--- |
| **Aparecium** | `Initialization` | Enabling Power/Clocks to a Peripheral |
| **Revelio** | `ADC_Read` | Sampling a 10-bit Voltage Value |
| **Lumos** | `PWM_Write` | Modulating Duty Cycle for Power Control |
| **Sonorus** | `UART_Transmit` | Pushing Bytes to the Serial Buffer |
| **Legilimens** | `String_Buffer` | Collecting Serial Data until a Newline |
| **Alohomora** | `I2C_Start` | Asserting a Start Condition on the Bus |


## Key Learnings
* I learned how to navigate technical datasheets by using a **"Search and Destroy"** strategy, focusing on Register Summaries and Bitfield Definitions rather than reading linearly.
* I mastered the **AVR memory map**, specifically understanding that while the ATmega328P is an **8-bit architecture**, its peripherals are mapped into a **16-bit memory space**.
* I discovered the **+0x20 address offset** required to access I/O registers as data space using C-pointers versus assembly instructions.
* I learned to handle **16-bit register access** in an 8-bit system, ensuring I write or read the **Low byte before the High byte** to maintain data integrity through the hardware’s internal temporary registers.
* I utilized **AVR intrinsics** and the `volatile` keyword to prevent the compiler from optimizing out necessary hardware interactions that change outside of the CPU's view.
* I implemented a professional **3-Layer HAL architecture**, separating raw Register addresses from the Logic layer (handshakes/polling) and the high-level API layer.
* I developed custom drivers for **GPIO**, managing the DDR, PORT, and PIN registers to control digital input/output at the bit level.
* I mastered **UART communication**, calculating the **UBRR** value manually based on clock frequency to establish precise baud rates for serial transmission.
* I built an **ADC driver** to sample analog voltages, learning how to manage the multiplexer and reference voltage registers to read sensors on pins A0-A5.
* I implemented **PWM (Pulse Width Modulation)** by configuring high-speed Timers to simulate analog output through duty-cycle control.
* I learned the mechanics of **Serial Peripheral Interface (SPI)** and **I2C (Two-Wire Interface)**, including how to manage bus start/stop conditions and data registers.
* I recognized and mitigated **Pin Contention**, learning that many pins have dual functions (like A4 being both an Analog input and I2C SDA) and must be initialized with "Targeted" logic.
* I applied **Bitwise Logic** (`|=`, `&= ~`, `^=`) to surgically manipulate specific bits within registers without affecting adjacent hardware settings.
* I learned to implement **Defensive Programming**, such as using buffer length checks during string reception to prevent memory corruption and system crashes.