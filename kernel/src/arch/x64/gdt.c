#include <kernel.h>

struct comp_packed {
    segment_descriptor_t gdts[5];
    system_segment_descriptor_t tss;
} gdt;

void init_gdt() {
    // null descriptor, off = 0
    gdt.gdts[0] = (segment_descriptor_t){ 0 };

    // 64 bit kernel code segment, off = 8
    gdt.gdts[1] = (segment_descriptor_t){
        0, 0, 0,
        // Present, Segment, Executable code, Read- and Writeable
        0b10011010,
        // flags Granularity and Long mode
        0b10100000, 0
    };
    // 64 bit kernel data segment, off = 16
    gdt.gdts[2] = (segment_descriptor_t){
        0, 0, 0,
        // Present, Segment, Read- and Writeable
        0b10010010,
        // flags Granularity and Long mode
        0b10100000, 0
    };
    // 64 bit user code segment, off = 24
    gdt.gdts[3] = (segment_descriptor_t){
        0, 0, 0,
        // Present, Segment, Read- and Writeable
        0b11111010,
        // flags Granularity and Long mode
        0b10100000, 0
    };
    // 64 bit user data segment, off = 32
    gdt.gdts[4] = (segment_descriptor_t){
        0, 0, 0,
        // Present, Segment, Read- and Writeable
        0b11110010,
        // flags Granularity and Long mode
        0b10100000, 0
    };

    // tss
    gdt.tss.descriptor.limit_low = sizeof(struct task_state_segment);
    gdt.tss.descriptor.base_low = 0;
    gdt.tss.descriptor.base_mid = 0;
    // Present, Executable, Accessed
    gdt.tss.descriptor.access_byte = 0b10001001;
    // size-bit
    gdt.tss.descriptor.limit_high_and_flags = 0;
    gdt.tss.descriptor.base_high = 0;
    gdt.tss.base = 0;
    gdt.tss.reserved = 0;

    gdtr_t gdtr = {
        .limit = sizeof(gdt) - 1,
        .gdt_ptr = (uintptr_t) &gdt
    };

    // gdtr size - 1
    gdtr.limit = (uint16_t)(sizeof(gdt) - 1);
    gdtr.gdt_ptr = (uintptr_t)&gdt;

    load_gdt(&gdtr);

    ok("Initialized GDT! Base: %p, Limit: 0x%X\n", gdtr.gdt_ptr, gdtr.limit);

}

void load_gdt(gdtr_t* gdtr) {
    __asm__ volatile (
        "mov %0, %%rdi\n"
        "lgdt (%%rdi)\n"
        "push $0x8\n" // 8: offset kernel code 64 bit
        "lea 1f(%%rip), %%rax\n"
        "push %%rax\n"
        "lretq\n"
        "1:\n"
        "mov $0x10, %%ax\n" // 16: offset kernel data 64 bit
        "mov %%ax, %%es\n"
        "mov %%ax, %%ss\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%fs\n"
        :
        : "r" (gdtr)
        : "memory"
    );
}
