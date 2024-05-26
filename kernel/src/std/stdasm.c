/*+===================================================================
  File:      STDASM.C

  Summary:   This file contains the implementation of the
             standard assembly functions in C

  Structs:   

  Functions: hlt: Halts the CPU
             init_sse: Initializes the SSE registers

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#include <kernel.h>

void hlt() {
    asm ("cli"); // Clear the interrupt flag
    for (;;) {
        asm ("hlt"); // Halt the CPU.... forever!!
    }
}

void init_sse() {

    int fcw = 0x037F;

    asm volatile (
    "fninit\n\t"
    "fldcw %0\n\t"
    "mov %%cr0, %%rax\n\t"
    "and $~0x04, %%al\n\t"
    "or $0x22, %%al\n\t"
    "mov %%rax, %%cr0\n\t"
    "mov %%cr4, %%rax\n\t"
    "or $0x600, %%ax\n\t"
    "mov %%rax, %%cr4"
    :
    : "m"(fcw)
    : "eax"
    );

}