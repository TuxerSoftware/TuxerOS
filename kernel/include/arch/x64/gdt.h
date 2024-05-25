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