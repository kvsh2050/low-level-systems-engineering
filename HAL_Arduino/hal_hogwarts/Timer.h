#ifndef TIMER_H
#define TIMER_H

#include "Registers.h"

// --- BIT DEFINITIONS (From Datasheet) ---
#define WGM01   1   // Waveform Generation Mode bit 1
#define WGM00   0   // Waveform Generation Mode bit 0
#define COM0A1  7   // Compare Match Output A bit 1
#define CS01    1   // Clock Select bit 1
#define CS00    0   // Clock Select bit 0
#define OCF0A   1   // Output Compare Flag A

// --- CTC MODE (For Delays) ---
static inline void Timer0_Init_CTC() {
    // 1. Set CTC Mode (WGM01 = 1, WGM00 = 0)
    TCCR0A = (1 << WGM01);
    
    // 2. Set Prescaler 64 (CS01=1, CS00=1)
    TCCR0B = (1 << CS01) | (1 << CS00);
}

static inline void delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; i++) {
        TCNT0 = 0; 
        OCR0A = 250; // 16MHz / 64 / 1000 = 250 ticks
        while (!(TIFR0 & (1 << OCF0A)));
        TIFR0 |= (1 << OCF0A); // Clear flag
    }
}

// --- PWM MODE (For Brightness/Speed) ---
static inline void Timer0_Init_PWM() {
    // 1. Set Fast PWM Mode (WGM01=1, WGM00=1)
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    
    // 2. Clear OC0A on Compare Match (Non-Inverting Mode)
    // This connects the Timer hardware directly to PD6 pin
    TCCR0A |= (1 << COM0A1);
    
    // 3. Set Prescaler 64
    TCCR0B |= (1 << CS01) | (1 << CS00);
    
    // Set PD6 (Arduino D6) as Output so the PWM signal can escape
    DDRD |= (1 << 6); 
}

static inline void PWM_SetDuty(uint8_t duty) {
    // 0 = Always OFF, 255 = Always ON
    OCR0A = duty;
}

#endif