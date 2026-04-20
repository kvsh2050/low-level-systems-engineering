#include "HP_HAL.h"

int main(void) {
    char parchment[64]; // Our string buffer

    Cast_VocemAperio(9600);
    Cast_Sonorus("The Great Hall is listening. Type a sentence and press Enter...\r\n");

    while(1) {
        // 1. Listen for a full sentence
        Cast_Legilimens(parchment, 64);

        // 2. Newline for clarity
        Cast_Sonorus("\r\nWizard Echoes: ");

        // 3. Repeat the full string back
        Cast_Sonorus(parchment);
        Cast_Sonorus("\r\n\r\n");
    }

    return 0;
}