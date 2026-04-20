#include "UART.h"
#include "Timer.h"

int main() {
    // Initialize with 8-bit, No Parity, 1 Stop Bit
    UART_Init(9600, UART_8_BIT, UART_PARITY_NONE, UART_STOP_1_BIT);

    char byte_received;

    UART_SendString("Serial Echo Test Starting...\r\n");

    while(1) {
        // 1. Wait for data to arrive from PC
        UART_ReceiveChar(&byte_received);

        delay_ms(5);

        // 2. Immediately send the same data back to PC
        UART_SendChar(byte_received);
    }
}