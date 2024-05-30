/*
  File:         idt.h
  Description:  Contains the Definitions for the IDT
				implementation
  Author:       RaphtikAtGHG
  Credits:      Leaf Kernel (hello@leafkern.xyz)
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

#define IDT_ENTRIES 256

typedef struct {
	uint16_t limit;
	uint64_t base;
} comp_packed idt_ptr_t;

typedef struct {
	uint16_t off_low;
	uint16_t sel;
	uint8_t ist;
	uint8_t flags;
	uint16_t off_middle;
	uint32_t off_high;
	uint32_t zero;
} comp_packed idt_entry_t;

typedef struct {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rbp;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;

	uint64_t vector;
	uint64_t err;

	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
} comp_packed idt_frame_t;




void set_idt_gate(int num, uint64_t base, uint16_t sel, uint8_t flags);
void init_idt();

