# **Technical Reference: AVR Hardware Abstraction Layer (HAL)**
**Target:** ATmega328P (16MHz)  
**Architecture:** Register-Logic-API (Three-Layer Firewall)

---

## **1. The Foundation: Registers.h**
This layer maps the physical silicon addresses to C-pointers. By bypassing standard libraries, we achieve **Zero-Overhead** memory access.

* **Key Mapping:**
    * **UART:** `0xC0 - 0xC6` (Control, Status, and Data)
    * **ADC:** `0x78 - 0x7C` (Multiplexer and Result)
    * **SPI:** `0x4C - 0x4E` (Control and Shift Register)
    * **I2C:** `0xB8 - 0xBC` (Bit Rate and Bus Control)

---

## **2. Peripheral Modules**

### **A. UART (Serial Communication)**
The "Voice" of the system.
* **Protocol:** Asynchronous Serial, 9600 Baud, 8-N-1.
* **Logic:** Uses **Polling** on the `UDRE0` and `RXC0` flags to ensure data integrity before reading or writing to the `UDR0` register.

### **B. Analog & PWM (Sensing & Output)**
* **ADC (Analog-A0):** Converts 0-5V into a 10-bit digital value ($0$ to $1023$).
* **PWM (Digital-D6):** Simulates analog voltage using high-speed digital switching (Fast PWM Mode).
* **The Bridge:** The software acts as the translator, scaling 10-bit input to 8-bit output.

### **C. Bus Protocols (SPI & I2C)**
* **SPI:** High-speed synchronous data transfer via the `SPDR` shift register. Used for displays and high-speed storage.
* **I2C:** Address-based bus communication on Pins A4/A5. Shared with the ADC hardware via internal pin multiplexing.

---

## **3. Build & Flash Workflow**
The system is automated using a custom **Makefile**.

1.  **Compile:** `avr-gcc` converts C to Object files.
2.  **Hex Generation:** `avr-objcopy` creates the flashable image.
3.  **Deployment:** `avrdude` pushes the code via the Arduino bootloader.

---

## **4. Memory Footprint & Efficiency**
| Module | Method | Efficiency |
| :--- | :--- | :--- |
| **GPIO** | `static inline` | 1-2 CPU Cycles |
| **UART** | Polling | Minimal RAM impact |
| **Timer** | CTC Mode | Cycle-accurate timing |

