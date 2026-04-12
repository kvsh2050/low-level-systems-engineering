#include "usart0.h"

/*
USART INIT 
Following Initialization is performed before using sending and receiving data 
- Baud Rate calculation
- Set Baud Rate 
- Configure Frame Format
- Enable Hardware
*/

int UART_init(uart_config configuration){
    //Enable Hardware
    int pmgt = configuration.power_mgt;
    int pm = enable_hardware(pmgt);
    if (pm == 0){
        printf("Hardware is ON via register: sucess!");
    } else {
        printf("Cannot ON hardware: failed!");
    }

    // Calculate Baudrate 
    int baud_rate = configuration.Baud_rate;
    int baud_success = baud_rate_calculation(baud_rate);
    if (baud_success == 0){
        printf("Baudrate calculation and setup setup sucess!");
    } else {
        printf("Baudrate calculation and setup failed!");
    }

    //Frame Format Setup 
    int data_b = configuration.data_bits;
    int stop_b = configuration.stop_bits;
    int parity_b = configuration.parity_bit;
    int ff_success = setup_frame_format(data_b, stop_b, parity_b);
    if (ff_success == 0){
        printf("frame format setup sucess!");
    } else {
        printf("frame format setup failed!");
    }
    
    //Enable Hardware comm
    int m = enable_comm();
    if (m == 0){
        printf("Hardware is ON via register: sucess!");
    } else {
        printf("Cannot ON hardware: failed!");
    }
}

int baud_rate_calculation(baud_rate){
    //Calculate Baud 
    int ubbrn = (F_OSC /(16*baud_rate)) - 1;
    //Put this value into the UBBRn Register 
    UBRR0H = ubbrn & (0xFF);
    UBRR0L = ubbrn >> 8 ;
    return 0;
}

int enable_hardware (pmgt){
    //Set 0 to PRR to enable hardware
    PRR = pmgt;
    return 0;
}

int setup_frame_format(data_b, stop_b, parity_b) {
    //Set Uart mode 
    //6 and 7 bit of the C : UMSEL01, UMSEL00
    UCSR0C &= ~(1<<6);
    UCSR0C &= ~(1<<7);

    //5,4 is parity : no parity : 00 
    UCSR0C &= ~(1<<5);
    UCSR0C &= ~(1<<4);

    //stop bit selection
    UCSR0C &= ~(1<<3);  // 0 for 1 stop bit

    // We need to change and set 3 control and status registers to uart and setup 
    UCSR0B &= ~(1<<2) ;         //In uart mode: UCSZ02 = 0 UCSZ00, UCSZ01 = 1 for 8 bit
    UCSR0C |= 0x11;             
}

int enable_comm(){
    // Bit 4 and bit 3 - 3:tx and 4 :rx 
    // RX
    UCSR0B = (1 << 4);
    // TX
    UCSR0B = (1 << 3);
}
