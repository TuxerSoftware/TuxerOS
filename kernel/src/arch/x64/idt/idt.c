/*
  File:         idt.c
  Description:  Contains the implementation for the IDT
  Author:       RaphtikAtGHG
  Credits:	  	Leaf Kernel (hello@leafkern.xyz)
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

aligned(0x10) static idt_entry_t idt[256];
idt_ptr_t idt_p;

extern uint64_t isr_tbl[];
extern void load_idt(uint64_t);

void set_idt_gate(int num, uint64_t base, uint16_t sel, uint8_t flags)
{
	idt[num].off_low = (base & 0xFFFF);
	idt[num].off_middle = (base >> 16) & 0xFFFF;
	idt[num].off_high = (base >> 32) & 0xFFFFFFFF;
	idt[num].sel = sel;
	idt[num].ist = 0;
	idt[num].flags = flags;
	idt[num].zero = 0;
}

void init_idt()
{
	idt_p.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_p.base = (uint64_t)&idt;

	asm("sti");
	for (int i = 0; i < 256; ++i) {
		set_idt_gate(i, isr_tbl[i], 0x08, 0x8E);
	}

	load_idt((uint64_t)&idt_p);
	asm("cli");

	ok("IDT initialized. Base: 0x%p, Limit: 0x%X\n", idt_p.base, idt_p.limit);
}

void excp_handler(idt_frame_t frame)
{
	if (frame.vector < 0x20) {
		uint64_t ecns = getBits(frame.err, 0, 18);
		uint64_t bec = ecns;
		setBit(&bec, 0);
		setBit(&bec, 1);
		panic(frame, bec, "CPU Exception: 0x%X", frame.vector);
		hlt();
	} else if (frame.vector >= 0x20 && frame.vector <= 0x2f) {
		printf("IRQ: %d\n", frame.vector - 0x20);
	} else if (frame.vector == 0x80) {
		// TODO: Handle system calls.
	}
}
