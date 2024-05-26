/*+===================================================================
  File:      GDT.H

  Summary:   This file is the header file for the Global
             Descriptor Table (GDT) declerations.

  Structs:   segment_descriptor: Structure for a GDT entry.
             system_segment_descriptor: Structure for a system
             segment descriptor.

  Functions: init_gdt: Initializes the GDT.
             load_gdt: Loads the GDT using inline assembly.

  Defines:   

  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
} comp_packed segment_descriptor;

// for tss and ldt
typedef struct {
    segment_descriptor descriptor;
    uint32_t base;
    uint32_t reserved;
} comp_packed system_segment_descriptor;

void init_gdt();
void load_gdt();