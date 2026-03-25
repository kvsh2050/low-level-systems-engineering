#define __SFR_OFFSET 0

#include "avr/io.h"

.global main

main:
  sbi   DDRB, 5     ; Set PB5 as output

blink:
  sbi   PINB, 5     ; Toggle PINB
  ldi   r25, hi8(500)
  ldi   r24, lo8(500)
  call  delay_ms
  jmp   blink

delay_ms:
  ; Delay about (r25:r24)*ms. Clobbers r30, and r31.
  ; One millisecond is about 16000 cycles at 16MHz.
  ; The inner loop takes 4 cycles, so we repeat it 3000 times
  ldi   r31, hi8(4000)
  ldi   r30, lo8(4000)
inner:
  sbiw    r30, 1
  brne    inner
  sbiw    r24, 1
  brne    delay_ms
  ret

