#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
    // STEP 1: Set PB5 as OUTPUT
    // Hint: which register? which bit? which operation?
    DDRB |= (1 << 5);

    while (1) {
        // STEP 2: Turn LED ON
        // Hint: which register controls the pin voltage level?
        PORTB |= (1 << 5);

        // STEP 3: Wait 500ms
        _delay_ms(500);

        // STEP 4: Turn LED OFF
        // Hint: AND with NOT of the bitmask
        PORTB &= ~(1 << 5);

        // STEP 5: Wait again
        _delay_ms(500);
    }
    return 0;
}