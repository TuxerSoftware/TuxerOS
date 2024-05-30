/*
  File:         cpu.h
  Description:  Contains the Definitions for the CPU 
                routines implementation
  Author:       RaphtikAtGHG  
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

typedef struct task_state_segment {
    uint32_t reserved_0;
    uint64_t rsp0;  // privilege level stacks
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved_1;
    uint64_t ist1;  // additional stack (IDT IST)
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved_2;
    uint16_t reserved_3;
    uint16_t iomba;
} task_state_segment_t;
