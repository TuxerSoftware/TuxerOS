/*
  File:         panic.c
  Description:  Contains the implementation for the panic
                routines
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

void panic(idt_frame_t frame, int backupErrorCode ,const char* message, ...) {
    va_list args;
    va_start(args, message);
    printf("PANIC: ");
    vprintf(message, args);
    va_end(args);
    printf("\n\n");
    if (frame.err != 0) {
        printf("Error code: 0x%X\n", frame.err);
    } else {
        printf("Error code: 0x%X\n", backupErrorCode);
    }

    printf("RIP: 0x%p\n", frame.rip);
    printf("RSP: 0x%p\n", frame.rsp);
    printf("RBP: 0x%p\n", frame.rbp);
    printf("RAX: 0x%p\n", frame.rax);
    printf("RBX: 0x%p\n", frame.rbx);
    printf("RCX: 0x%p\n", frame.rcx);
    printf("RDX: 0x%p\n", frame.rdx);
    printf("RSI: 0x%p\n", frame.rsi);
    printf("RDI: 0x%p\n", frame.rdi);
    printf("R8: 0x%p\n", frame.r8);
    printf("R9: 0x%p\n", frame.r9);
    printf("R10: 0x%p\n", frame.r10);
    printf("R11: 0x%p\n", frame.r11);
    printf("R12: 0x%p\n", frame.r12);
    printf("R13: 0x%p\n", frame.r13);
    printf("R14: 0x%p\n", frame.r14);
    printf("R15: 0x%p\n", frame.r15);
    printf("CS: 0x%p\n", frame.cs);
    printf("SS: 0x%p\n", frame.ss);
    printf("RFLAGS: 0x%p\n", frame.rflags);

    hlt();
}