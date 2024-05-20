#include <kernel.h>

struct flanterm_context *ft_ctx;

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

    struct limine_file *file = getKernel();

    

    ok("Kernel file: %s, Size %dKB, Address: %p, CMD-Line: %s\n", file->path, bytesToKB(file->size), file->address, file->cmdline);

    hlt();
}