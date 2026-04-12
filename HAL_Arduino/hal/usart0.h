//Memory Regions 
#define UDR0    (*(volatile unsigned char *)0xC6) 
#define UCSR0A  (*(volatile unsigned char *)0xC0)
#define UCSR0B  (*(volatile unsigned char *)0xC1)
#define UCSR0C  (*(volatile unsigned char *)0xC2)
#define UBRR0L  (*(volatile unsigned char *)0xC4)
#define UBRR0H  (*(volatile unsigned char *)0xC5)
#define PRR     (*(volatile unsigned char *)0x64)

//Clock 
#define F_OSC 16000000

//Configuration struct 
typedef struct usart0
{
    int data_bits;
    int parity_bit;
    int Baud_rate;
    int stop_bits;
    int power_mgt;
} uart_config;

//Function declaration 
int UART_init(uart_config configuration);