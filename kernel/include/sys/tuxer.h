#ifndef TUXER_H
#define TUXER_H

#include <limine.h>

// VERSION INFO
#define TUXER_VERSION_MAJOR 0
#define TUXER_VERSION_MINOR 1
#define TUXER_VERSION_PATCH 0
#define VERSION_CODENAME "Jelly-Cow"
#define VERSION_STRING "0.1.0-Jelly-Cow"

// REQUESTS
__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

__attribute__((used, section(".requests")))
volatile static struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

volatile static struct limine_kernel_file_request kernel = {
    .id = LIMINE_KERNEL_FILE_REQUEST,
    .revision = 0
};


__attribute__((used, section(".requests")))
volatile static struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

__attribute__((used, section(".requests")))
volatile static struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};



// MODULE INDEXES
#define MODULE_INDEX_RAMFS 0

// LIMINE OBJECTS
struct limine_framebuffer *getFramebuffer();
struct limine_file *getModule(int index);
struct limine_file *getKernel();

#endif // TUXER_H