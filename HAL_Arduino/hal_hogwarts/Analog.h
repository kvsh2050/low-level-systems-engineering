#ifndef ANALOG_H
#define ANALOG_H

#include "Registers.h"

// --- BIT DEFINITIONS ---
#define ADEN    7   // ADC Enable
#define ADSC    6   // ADC Start Conversion
#define REFS0   6   // Reference selection (Vcc)

static inline void ADC_Init() {
    // 1. Set Reference to AVcc (5V)
    ADMUX = (1 << REFS0);

    // 2. Enable ADC + Set Prescaler to 128 (16MHz/128 = 125KHz)
    // 125KHz is the required frequency for 10-bit accuracy
    ADCSRA = (1 << ADEN) | (1 << 2) | (1 << 1) | (1 << 0);
}

static inline uint16_t AnalogRead(uint8_t channel) {
    // 1. Select Channel (A0-A5). Masking ensures we don't overwrite REFS bits.
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // 2. Start Conversion
    ADCSRA |= (1 << ADSC);

    // 3. Wait for conversion to finish (Hardware clears ADSC bit when done)
    while (ADCSRA & (1 << ADSC));

    // 4. Return the combined 16-bit result (ADCL + ADCH)
    return ADC_RES;
}

#endif