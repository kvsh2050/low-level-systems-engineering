#include "usart0.h"

void baud_rate_calculation(int baud_rate){
    //Calculate Baud 
    int ubbrn = (F_OSC /(16 * baud_rate)) - 1;
    //Put this value into the UBBRn Register
    UBRR0H = ubbrn >> 8; 
    UBRR0L = ubbrn & (0xFF);
}

void enable_hardware (uint8 pmgt){ 
    //Set 0 to PRR to enable hardware
    PRR &= ~(1 << PRUSART0) ;
}

void setup_frame_format(uint8 data_b, uint8 stop_b, uint8 parity_b) {
    //Set Uart mode 
    //6 and 7 bit of the C : UMSEL01, UMSEL00
    UCSR0C &= ~(1 << UMSEL00);
    UCSR0C &= ~(1 << UMSEL01);

    //5,4 is parity : no parity : 00 
    UCSR0C &= ~(1 << UPM01);
    UCSR0C &= ~(1 << UPM00);

    //stop bit selection
    UCSR0C &= ~(1 << USBS0);  // 0 for 1 stop bit

    // We need to change and set 3 control and status registers to uart and setup 
    UCSR0B &= ~(1 << UCSZ02) ;         //In uart mode: UCSZ02 = 0 UCSZ00, UCSZ01 = 1 for 8 bit
    UCSR0C |= 0x6;              // 110 in bin == 6 in hex    
}

void enable_comm(){
    // Bit 4 and bit 3 - 3:tx and 4 :rx 
    // RX
    UCSR0B |= (1 << RXEN0);
    // TX
    UCSR0B |= (1 << TXEN0);
}

//Transmit
void UART_send(uint8 data){
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
    uint8 baud_rate = configuration.Baud_rate;
    baud_rate_calculation(baud_rate);

    //Frame Format Setup 
    uint8 data_b = configuration.data_bits;
    uint8 stop_b = configuration.stop_bits;
    uint8 parity_b = configuration.parity_bit;
    setup_frame_format(data_b, stop_b, parity_b);
    
    //Enable Hardware comm
    enable_comm();
}

