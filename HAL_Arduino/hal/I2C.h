#ifndef I2C_H
#define I2C_H

#include "Registers.h"

// --- BIT DEFINITIONS (TWCR Register) ---
#define TWINT   7   // TWI Interrupt Flag
#define TWSTA   5   // TWI Start Condition Bit
#define TWSTO   4   // TWI Stop Condition Bit
#define TWEN    2   // TWI Enable Bit

static inline void I2C_Init() {
    // Set Bit Rate: SCL freq = F_CPU / (16 + 2*TWBR * Prescaler)
    TWBR = 72; // Standard 100kHz for 16MHz Clock
}

static inline void I2C_Start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

static inline void I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

static inline void I2C_Stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

#endif