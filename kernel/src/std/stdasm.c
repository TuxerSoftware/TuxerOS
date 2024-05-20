#include <std/stdasm.h>

void hlt() {
    asm ("cli"); // Clear the interrupt flag
    for (;;) {
        asm ("hlt"); // Halt the CPU.... forever!!
    }
}