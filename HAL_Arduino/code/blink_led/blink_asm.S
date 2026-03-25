#define __SFR_OFFSET 0   // makes sure that you use i/o address not memory mapped data reg  

#include <avr/io.h>

.global main

main:
    sbi DDRB, 5    ; PB5 output
    cbi PORTB, 5   ; LED OFF first

loop:
    sbi PORTB, 5   ; LED ON
    call delay_ms
    cbi PORTB, 5   ; LED OFF
    call delay_ms
    jmp loop


delay_ms:
    ldi r16, 2
L1:
    ldi r17, 200
L2:
    ldi r18, 200
L3:
    ldi r19, 200
L4:
    dec r19
    brne L4

    dec r18
    brne L3

    dec r17
    brne L2

    dec r16
    brne L1

    ret