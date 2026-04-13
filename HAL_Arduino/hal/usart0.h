#ifndef USART0_H
#define USART0_H

//Datatype of the data sent : 8 bits so char
typedef unsigned char uint8;

//Memory Regions 
#define UDR0    (*(volatile unsigned char *)0xC6) 
#define UCSR0A  (*(volatile unsigned char *)0xC0)
#define UCSR0B  (*(volatile unsigned char *)0xC1)
#define UCSR0C  (*(volatile unsigned char *)0xC2)
#define UBRR0L  (*(volatile unsigned char *)0xC4)
#define UBRR0H  (*(volatile unsigned char *)0xC5)
#define PRR     (*(volatile unsigned char *)0x64)

//Register Map

//UCSR0A 
#define RXC0    7
#define TXC0    6
#define UDRE0   5
#define FE0     4
#define DOR0    3
#define UPE0    2
#define U2X0    1
#define MPCM0   0

// UCSR0B 
#define RXCIE0  7
#define TXCIE0  6
#define UDRIE0  5
#define RXEN0   4
#define TXEN0   3
#define UCSZ02  2
#define RXB80   1
#define TXB80   0

// UCSR0C 
#define UMSEL01 7
#define UMSEL00 6
#define UPM01   5
#define UPM00   4
#define USBS0   3
#define UCSZ01  2
#define UDORD0  2 // MSPIM Alias
#define UCSZ00  1
#define UCPHA0  1 // MSPIM Alias
#define UCPOL0  0

//Power
#define PRUSART0 1

//Clock 
#define F_OSC 16000000UL

//Configuration struct 
typedef struct usart0
{
    //Frame Format
    uint8 data_bits;
    uint8 parity_bit;
    uint8 stop_bits;
    //Baud Rate 
    int Baud_rate;
    //Power
    uint8 power_mgt;
} uart_config;

//Function declaration 
void UART_init(uart_config configuration);
void UART_send(uint8 data);
uint8 UART_rcv(void);

#endif