#include "uart.h"

int main(){
    //Intialize 
    USART_Init(9600);

    //Print in loop 
    while(1){
        char intro = 'H';
        USART_Tx(intro);
    }
}