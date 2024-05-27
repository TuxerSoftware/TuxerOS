/*+===================================================================
  File:      IDT.C

  Summary:   This file contains the implementation of the
             Interrupt Descriptor Table (IDT) in C

  Structs:   

  Functions: 

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#include <kernel.h>

void interrupt_handler() {
    printf("Interrupt!\n");

    hlt();
}

idt_entry_t __priv_init_entry(uint64_t base, uint8_t flags) {
    return (idt_entry_t){
        .isr_low = base & 0xFFFF,
        .isr_mid = (base >> 16) & 0xFFFF,
        .isr_high = (base >> 32) & 0xFFFFFFFF,
        .kernel_cs = 0x08,
        .ist = 0,
        .attributes = flags,
        .reserved = 0
    };
}

aligned(0x10) static idt_entry_t idt_entries[IDT_ENTRIES];

void init_idt() {
    idt_ptr_t idt_p = (idt_ptr_t){
        .limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1,
        .base = (uintptr_t)&idt_entries,
    };

    for (uint16_t i = 0; i < IDT_ENTRIES; i++) {
        idt_entries[i] = __priv_init_entry((uintptr_t)&interrupt_handler, 0x8E);
    }

    asm("lidt %0" : : "m"(idt_p) : "memory");
    asm("sti");

    printf("IDT Initialized. Base: 0x%p, Limit: 0x%X\n", (void*)idt_p.base, idt_p.limit);
}
