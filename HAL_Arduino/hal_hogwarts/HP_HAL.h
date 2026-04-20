#ifndef HP_HAL_H
#define HP_HAL_H

#include "Registers.h"
#include "GPIO.h"
#include "UART.h"
#include "Analog.h"
#include "PWM.h"
#include "SPI.h"
#include "I2C.h"

// --- [ACT 0: TARGETED TRANSFIGURATIONS (Init)] ---
static inline void Cast_VocemAperio()      { UART_Init(9600, UART_8_BIT, UART_PARITY_NONE, UART_STOP_1_BIT); }
static inline void Cast_HomenumRevelio()   { ADC_Init(); }
static inline void Cast_SpecialisRevelio() { I2C_Init(); }
static inline void Cast_LumosAperio()      { PWM_Init(); }

// --- [ACT 1: SENSING & LIGHT] ---
static inline uint16_t Cast_Revelio(uint8_t ch) { return AnalogRead(ch); }
static inline void     Cast_Lumos(uint8_t bri)  { AnalogWrite(bri); }

// --- [ACT 2: COMMUNICATION (UART/SPI)] ---
static inline void    Cast_Sonorus(const char* s) { UART_SendString(s); }
static inline uint8_t Cast_PointMe(uint8_t d)     { return SPI_Transfer(d); }

// --- [ACT 3: THE BUS (I2C)] ---
static inline void Cast_Alohomora()             { I2C_Start(); }
static inline void Cast_Scripto(uint8_t d)      { I2C_Write(d); }
static inline void Cast_Colloportus()           { I2C_Stop(); }

// --- [ACT 4: THE FINISH (Cleanup)] ---
static inline void Cast_FiniteIncantatem() {
    ADCSRA &= ~(1 << 7); // Disable ADC
    UCSR0B &= ~((1 << 4) | (1 << 3)); // Disable UART
}
// HP_HAL.h

/**
 * @brief Ausculto: Listens for a single magical whisper (character) from the air.
 * Hardware: UART Receiver (RX).
 */
static inline char Cast_Ausculto() {
    // Wait for data to be received (polling the RXC0 flag)
    while (!(UCSR0A & (1 << 7))); 
    return UDR0; // Return the received byte
}

/**
 * @brief Dictum: Echoes a single character back out.
 */
static inline void Cast_Dictum(char c) {
    while (!(UCSR0A & (1 << 5))); // Wait for empty transmit buffer
    UDR0 = c;
}

// HP_HAL.h

/**
 * @brief Legilimens: Reads a full string until a newline (\n) or carriage return (\r).
 * @param buffer The parchment where the string is stored.
 * @param max_length The size of the parchment to prevent overflow.
 */
static inline void Cast_Legilimens(char* buffer, uint8_t max_length) {
    uint8_t index = 0;
    char received_char;

    while (index < (max_length - 1)) {
        received_char = Cast_Ausculto(); // Listen for one char

        // Check for "Enter" key (Carriage Return or Newline)
        if (received_char == '\r' || received_char == '\n') {
            break; 
        }

        buffer[index] = received_char;
        index++;
        
        // Optional: Echo the char back immediately so the user sees what they type
        //Cast_Dictum(received_char); 
    }
    
    buffer[index] = '\0'; // The "Null Terminator" - ends the string
}
#endif