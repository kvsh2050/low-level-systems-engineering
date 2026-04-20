#ifndef PWM_H
#define PWM_H

#include "Registers.h"

// --- BIT DEFINITIONS (TCCR0A/B) ---
#define COM0A1  7   // Compare Output Mode for Channel A
#define WGM01   1   // Waveform Generation Mode bit 1
#define WGM00   0   // Waveform Generation Mode bit 0
#define CS01    1   // Clock Select bit 1 (Prescaler)
#define CS00    0   // Clock Select bit 0 (Prescaler)

/**
 * @brief Initializes Timer0 for Fast PWM on Pin PD6 (OC0A)
 * Frequency calculation: F_CPU / (Prescaler * 256)
 * 16MHz / (64 * 256) = ~976 Hz
 */
static inline void PWM_Init() {
    // 1. Set PD6 (Digital Pin 6) as Output
    // This is the physical pin tied to OC0A
    DDRD |= (1 << 6);

    // 2. Set Fast PWM Mode (WGM01 and WGM00 both 1)
    // 3. Set Non-Inverting Mode (COM0A1 = 1)
    // This clears the pin on match and sets it at BOTTOM
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

    // 4. Set Prescaler to 64 (CS01 and CS00 both 1)
    TCCR0B = (1 << CS01) | (1 << CS00);
}

/**
 * @brief Sets the duty cycle for the PWM output
 * @param duty 0 (Always Low) to 255 (Always High)
 */
static inline void AnalogWrite(uint8_t duty) {
    // Updating this register changes the "flip point" of the signal
    OCR0A = duty;
}

#endif