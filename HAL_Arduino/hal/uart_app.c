#include "usart0.h"

int main(){
    //Setup
    uart_config usart;
    usart.data_bits = 8;
    usart.Baud_rate = 9600;
    usart.parity_bit = 0;
    usart.stop_bits = 0;
    usart.power_mgt = 0;

    UART_init(usart);

    //Loop 
    while(1){
        UART_send('H');
    }
    return 0;
}
