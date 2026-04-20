#include <stdint.h>
#include <stdio.h>

int main(){
    volatile uint8_t var = 1;

    while (!var){
        printf("Hi\n");
    }
}
