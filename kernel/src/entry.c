/*
  File:         entry.c
  Description:  Contains the kernel entry point
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

struct flanterm_context *ft_ctx;

extern void kmain();



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

    assert(1 != 1);

    int test = (int)NULL;

    nullAssert(test);

    hlt();
}