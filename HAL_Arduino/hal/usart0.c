//Memory Regions 
#define UDR0 0xC6 
#define UCSR0A 0xC0
#define UCSR0B 0xC1
#define UCSR0C 0xC2
#define UBRR0L 0xC4
#define UBRR0H 0xC5
#define PRR 0x64

//Configuration struct 
typedef struct usart0
{
    int data_bits;
    int parity_bit;
    int Baud_rate;
    int stop_bits;
    int error_detection;   
    int power_mgt;
} uart_config;


//Function declaration 
void UART_init(uart_config configuration);