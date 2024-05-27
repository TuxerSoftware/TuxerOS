/*+===================================================================
  File:      IDT.H

  Summary:   This file is the header file for the Interrupt
             Descriptor Table (IDT) declerations.

  Structs:   idt_entry_t: Structure for an IDT entry.
             idt_ptr_t: Structure for an IDT pointer.

  Functions: init_idt: Initializes the IDT.

  Defines:   IDT_ENTRIES: The number of entries in the IDT.

  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

#define IDT_ENTRIES 256

typedef struct idt_entry {
  uint16_t isr_low;
  uint16_t kernel_cs;
  uint8_t ist;
  uint8_t attributes;
  uint16_t isr_mid;
  uint32_t isr_high;
  uint32_t reserved;
} comp_packed idt_entry_t;

typedef struct idt_ptr {
  uint16_t limit;
  uint64_t base;
} comp_packed idt_ptr_t;

void init_idt();
