#ifndef UART_H
#define UART_H

#include "Registers.h"

//Enums 
typedef enum {
    UART_5_BIT = 0,
    UART_6_BIT = (1 << 1),
    UART_7_BIT = (1 << 2),
    UART_8_BIT = (1 << 2) | (1 << 1)  // UCSZ01 and UCSZ00
} UART_DataSize;

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN = (1 << 5),      // UPM01
    UART_PARITY_ODD  = (1 << 5) | (1 << 4) // UPM01 and UPM00
} UART_Parity;

typedef enum {
    UART_STOP_1_BIT = 0,
    UART_STOP_2_BIT = (1 << 3)        // USBS0
} UART_StopBits;

// --- BIT DEFINITIONS (The Register Layer) ---
#define RXEN0   4
#define TXEN0   3
#define UDRE0   5
#define RXC0    7 // USART Receive Complete flag

// --- LOGIC LAYER (The Implementation) ---

/**
 * @brief Initializes UART with specific protocol settings
 * Calculation based on 16MHz Clock
 */
static inline void UART_Init(uint32_t baud, UART_DataSize size, UART_Parity parity, UART_StopBits stop) {
    // 1. Set Baud Rate (Baud Rate Generator)
    uint16_t ubrr_val = (16000000UL / (16UL * baud)) - 1;
    UBRR0H = (uint8_t)(ubrr_val >> 8);
    UBRR0L = (uint8_t)ubrr_val;

    // 2. Enable Transmitter and Receiver hardware
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // 3. Configure Frame Format (Protocol Dashboard)
    UCSR0C = size | parity | stop;
}

/**
 * @brief Sends a single byte of data
 */
static inline void UART_SendChar(char data) {
    // Wait for the Data Register Empty (UDRE0) flag
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

/**
 * @brief Sends a null-terminated string
 */
static inline void UART_SendString(const char* str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}

/**
 * @brief Receives a single byte of data
 */
static inline void UART_ReceiveChar(char* buffer) {
    // Wait for the Receive Complete (RXC0) flag
    while (!(UCSR0A & (1 << RXC0)));
    *buffer = UDR0;
}

#endif