//We need to provide the ifndef 
#include <stdint.h>

//Define typedef 
typedef struct uart_setup{
    uint8_t data;
    uint16_t baud_rate;
};

//Initializing 
void uart_init(void);

//Send data 
bool uart_send(char data);

//Receive the data 
char uart_rcv(void);




