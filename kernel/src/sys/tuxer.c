/*+===================================================================
  File:      TUXER.C

  Summary:   This file contains the functions and requests
             for the Tuxer kernel.

  Structs:   

  Functions: getFramebuffer: Gets the framebuffer.
             getModule: Gets a module.
             getKernel: Gets the kernel.
             getFramebufferResponse: Gets the framebuffer response.
             getModuleResponse: Gets the module response.
             getKernelResponse: Gets the kernel response.
             isBaseRevisionSupported: Checks if the base revision is supported.

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

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
volatile static struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
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