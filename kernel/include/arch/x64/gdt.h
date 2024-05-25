#pragma once

#include <kernel.h>

typedef struct segment_descriptor {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
} comp_packed segment_descriptor_t;

typedef struct system_segment_descriptor {
    segment_descriptor_t descriptor;
    uint32_t base;
    uint32_t reserved;
} comp_packed system_segment_descriptor_t;

typedef struct gdtr {
    uint16_t limit;
    uintptr_t gdt_ptr;
} comp_packed gdtr_t;

void init_gdt();
void load_gdt(gdtr_t* gdtr);