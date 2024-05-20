#include <kernel.h>

#include <sys/tuxer.h>
#include <std/stdasm.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void _start(void) {
    
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hlt();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hlt();
    }

    struct limine_framebuffer *framebuffer = getFramebuffer();

    hlt();
}
