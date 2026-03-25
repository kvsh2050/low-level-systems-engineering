#include <avr/io.h>

int main(void) {
    DDRB |= (1 << PB5);   // PB5 as output
    PORTB &= ~(1 << PB5); // drive LOW → LED OFF
    while (1);
}