/*
  File:         entry.c
  Description:  Contains the kernel entry point
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

struct flanterm_context *ft_ctx;

extern void kmain();

pmm_ctx_t pmm_ctx;

__attribute__((used, section(".requests")))
volatile struct limine_memmap_request memmap_request = { 
    .id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};

__attribute__((used, section(".requests")))
volatile struct limine_hhdm_request hhdm_request = { 
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0 
};

volatile struct limine_framebuffer *framebuffer;
volatile struct limine_memmap_response *memmap;
volatile struct limine_hhdm_response *hhdm;

void _start(void) {
    
    if (isBaseRevisionSupported() == false) {
        hlt();
    }

    if (getFramebufferResponse() == NULL
     || getFramebufferResponse()->framebuffer_count < 1) {
        hlt();
    }

    init_sse();

    struct limine_framebuffer *framebuffer = getFramebuffer();

    memmap = memmap_request.response;
	hhdm = hhdm_request.response;

    
    ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        0
    );

    init_gdt();
    init_idt();
    init_pmm(&pmm_ctx, memmap, hhdm);


    struct limine_file *file = getKernel();

    {
        double file_size = kbToMB(bytesToKB((double)file->size));

        int64_t mb_size = (int64_t)file_size;
        double kb_size = file_size - (double)mb_size;

        ok("Kernel Path: %s, Kernel Address: %p, Kernel Size: %dMB and %.0fKB, Complete Size %.3fMB, CMD Line: %s\n", file->path, file->address, mb_size, kb_size * 1000, file_size , file->cmdline);
        // NOTE: There os a wierd bug where I cant get the KB size over the decimal point. So I just multiply by a 1000 to get the 
        // first there digits after the decimal point infront of it :P. Also then I print the double with .0 so no decimal points.
        // This is very wierd ngl.
    }

    int status = init_ata();

    if(status != ATA_OKAY) {
        err("Failed to initialize ATA driver: 0x%X\n", status);
    }

    const PMBR_t* mbr = getPMBR();
    GPTPartTable_t gpt = getGPTPartTable();

    printf("PMBR:\n");
    printf("\tBoot Indicator: 0x%X\n", mbr->boot_indicator);
    printf("\tStarting Head: %d\n", mbr->starting_head);
    printf("\tStarting Sector Cylinder: %d\n", mbr->starting_sector_cylinder);
    printf("\tSystem ID: 0x%X\n", mbr->system_id);
    printf("\tEnding Head: %d\n", mbr->ending_head);
    printf("\tEnding Sector Cylinder: %d\n", mbr->ending_sector_cylinder);
    printf("\tStarting LBA: %d\n", mbr->starting_lba);
    printf("\tEnding LBA: %d\n", mbr->ending_lba);


    hlt();
}