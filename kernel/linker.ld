/*
  File:         linker.ld
  Description:  Contains the linker script for the TuxerOS kernel
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)

PHDRS
{
    requests PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; /* Write + Read */
    text     PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ; /* Execute + Read */
    rodata   PT_LOAD    FLAGS((1 << 2)) ;            /* Read only */
    data     PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; /* Write + Read */
    dynamic  PT_DYNAMIC FLAGS((1 << 1) | (1 << 2)) ; /* Dynamic PHDR for relocations */
}

SECTIONS
{

    . = 0xffffffff80000000;

    .requests : {
        KEEP(*(.requests_start_marker))
        KEEP(*(.requests))
        KEEP(*(.requests_end_marker))
    } :requests

    . += CONSTANT(MAXPAGESIZE);

    .text : {
        *(.text .text.*)
    } :text

    . += CONSTANT(MAXPAGESIZE);

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    . += CONSTANT(MAXPAGESIZE);

    .data : {
        *(.data .data.*)
    } :data

    .dynamic : {
        *(.dynamic .dynamic.* .dyn .dyn.*)
    } :data :dynamic

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data

    
    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}
