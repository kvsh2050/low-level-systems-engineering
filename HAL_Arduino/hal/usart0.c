#include "usart0.h"
#include <stdint.h>

void baud_rate_calculation(uint32_t baud_rate){
    // Using 16UL ensures 32-bit math for the whole expression
    uint32_t ubbrn = ((F_OSC + (8UL * baud_rate)) / (16UL * baud_rate)) - 1;
    UBRR0H = (uint8_t)(ubbrn >> 8); 
    UBRR0L = (uint8_t)(ubbrn & 0xFF);
}   

void enable_hardware (uint8_t pmgt){ 
    //Set 0 to PRR to enable hardware
    //CLEAR first 
    PRR = 0;
    if (!pmgt){
        PRR &= ~(1 << PRUSART0);
    }else {
        PRR |= (1 << PRUSART0);
    }
}

void setup_frame_format(uint8 data_b, uint8 stop_b, uint8 parity_b) {
    // 1. Clear ONLY the bits we are about to set to ensure a clean state
    // We clear Parity (5:4), Stop Bit (3), and Character Size (2:1)
    UCSR0C &= ~((1 << UPM01) | (1 << UPM00) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00));

    // 2. STOP BITS
    if (stop_b == 2) {
        UCSR0C |= (1 << USBS0);
    } 
    // No 'else' needed if we cleared it above, but safe to keep for clarity.

    // 3. PARITY BITS
    if (parity_b == 1) {  // Even
        UCSR0C |= (1 << UPM01);
    } else if (parity_b == 2) { // Odd
        UCSR0C |= (1 << UPM01) | (1 << UPM00);
    } else {  //No Parity 
        UCSR0C &= ~((1 << UPM01) | (1 << UPM00)); 
    }

    // 4. DATA BITS
    if (data_b == 6) {
        UCSR0C |= (1 << UCSZ00);
    } else if (data_b == 7) {
        UCSR0C |= (1 << UCSZ01);
    } else if (data_b == 8) {
        UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
        UCSR0B &= ~(1 << UCSZ02); // Ensure 9th bit is off
    } else if (data_b == 9) {
        UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
        UCSR0B |= (1 << UCSZ02);  // Enable 9th bit
    }
}

void enable_comm(){
    // Bit 4 and bit 3 - 3:tx and 4 :rx 
    // RX
    UCSR0B |= (1 << RXEN0);
    // TX
    UCSR0B |= (1 << TXEN0);
}

//Transmit
void UART_send(uint8_t data){
    while (!(UCSR0A & (1 << UDRE0))){   // 1 - empty then send : until then wait in loop then you send data
        continue;
    }
    UDR0 = data;
}

//receive
uint8 UART_rcv(void){
    uint8 rvcd;
    while (!(UCSR0A & (1 << RXC0))){   // 1 - some data present : until then wait in loop then you receive
       continue;
    }
    rvcd = UDR0;
    return rvcd;
}

/*
USART INIT 
Following Initialization is performed before using sending and receiving data 
- Baud Rate calculation
- Set Baud Rate 
- Configure Frame Format
- Enable Hardware
*/

void UART_init(uart_config configuration){
    //Enable Hardware
    uint8 pmgt = configuration.power_mgt;
    enable_hardware(pmgt);

    // Calculate Baudrate 
    uint32_t baud_rate = configuration.Baud_rate;
    baud_rate_calculation(baud_rate);

    //Frame Format Setup 
    uint8_t data_b = configuration.data_bits;
    uint8_t stop_b = configuration.stop_bits;
    uint8_t parity_b = configuration.parity_bit;
    setup_frame_format(data_b, stop_b, parity_b);
    
    //Enable Hardware comm
    enable_comm();
}

