#ifndef SPI_H
#define SPI_H

#include "Registers.h"

// --- BIT DEFINITIONS (SPCR Register) ---
#define SPE     6   // SPI Enable
#define MSTR    4   // Master/Slave Select
#define SPR0    0   // SPI Clock Rate Select 0
#define SPIF    7   // SPI Interrupt Flag (in SPSR)

static inline void SPI_Init() {
    // 1. Set MOSI, SCK, and SS as Output
    DDRB |= (1 << 3) | (1 << 5) | (1 << 2);
    
    // 2. Enable SPI, Set as Master, Clock = F_CPU/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

static inline uint8_t SPI_Transfer(uint8_t data) {
    // 1. Load data into the Shift Register
    SPDR = data;

    // 2. Wait for transmission to complete (SPIF flag)
    while (!(SPSR & (1 << SPIF)));

    // 3. Return the data received from the peripheral
    return SPDR;
}

#endif