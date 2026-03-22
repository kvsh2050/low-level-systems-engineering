// No includes at all — everything defined by hand

// Register addresses straight from the ATmega328P datasheet
#define DDRB  (*(volatile unsigned char *)0x24)
#define PORTB (*(volatile unsigned char *)0x25)

// Simple delay loop — not perfectly calibrated but works visibly
static void delay_loop(unsigned long count) {
    while (count--) {
        __asm__ volatile ("nop");  // one CPU cycle, prevents optimizer removing the loop
    }
}

// At 16MHz, roughly 1ms ≈ 16000 iterations of a simple loop
#define DELAY_MS(ms)  delay_loop((ms) * 16000UL)

int main(void) {

    // Set PB5 as output
    DDRB |= (1 << 5);

    while (1) {
        PORTB |= (1 << 5);    // LED on
        DELAY_MS(500);

        PORTB &= ~(1 << 5);   // LED off
        DELAY_MS(500);
    }

    return 0;
}