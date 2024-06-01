/*
  File:         tuxer.c
  Description:  Contains the implementation for the TuxerOS
                routines and limine requests
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <sys/tuxer.h>
#include <kernel.h>

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

__attribute__((used, section(".requests")))
volatile static struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".requests")))
volatile static struct limine_kernel_file_request kernel = {
    .id = LIMINE_KERNEL_FILE_REQUEST,
    .revision = 0
};

__attribute__((used, section(".requests")))
volatile static struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

struct limine_framebuffer *getFramebuffer() {
    return framebuffer_request.response->framebuffers[0];
};

struct limine_file *getModule(int index) {
    return module_request.response->modules[index];
};
struct limine_file *getKernel() {
    return kernel.response->kernel_file;
};

struct limine_framebuffer_response *getFramebufferResponse() {
    return framebuffer_request.response;
};

struct limine_module_response *getModuleResponse() {
    return module_request.response;
};

struct limine_kernel_file_response *getKernelResponse() {
    return kernel.response;
};

bool isBaseRevisionSupported() {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        return false;
    }
    return true;
};