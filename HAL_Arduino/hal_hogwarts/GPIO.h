//Layer 2 - Driver + API 
#ifndef GPIO_H 
#define GPIO_H 

#include "Registers.h"

/*
There are 3 regsiters that we need to take into consideration when it comes to gpio
1. DDR 
2. PORT 
3. PIN 
*/

/*
PORTS
1. B: PB0-7, Digital IO 
2. C: PC0-6, Analog IO 
3. D: PD0-7, Digital IO, UART, Interrupts
*/

// API Constants
#define OUTPUT 1
#define INPUT  0
#define HIGH   1
#define LOW    0

static inline void GPIO_PinMode(char port, uint8_t pin, uint8_t mode) {
    switch(port) {
        case 'B': (mode == OUTPUT) ? (DDRB |= (1 << pin)) : (DDRB &= ~(1 << pin)); break;
        case 'C': (mode == OUTPUT) ? (DDRC |= (1 << pin)) : (DDRC &= ~(1 << pin)); break;
        case 'D': (mode == OUTPUT) ? (DDRD |= (1 << pin)) : (DDRD &= ~(1 << pin)); break;
    }
}

static inline void GPIO_Write(char port, uint8_t pin, uint8_t state) {
    switch(port) {
        case 'B': (state == HIGH) ? (PORTB |= (1 << pin)) : (PORTB &= ~(1 << pin)); break;
        case 'C': (state == HIGH) ? (PORTC |= (1 << pin)) : (PORTC &= ~(1 << pin)); break;
        case 'D': (state == HIGH) ? (PORTD |= (1 << pin)) : (PORTD &= ~(1 << pin)); break;
    }
}

static inline uint8_t GPIO_Read(char port, uint8_t pin) {
    switch(port) {
        case 'B': return (PINB & (1 << pin)) ? 1 : 0;
        case 'C': return (PINC & (1 << pin)) ? 1 : 0;
        case 'D': return (PIND & (1 << pin)) ? 1 : 0;
        default:  return 0;
    }
}

#endif


