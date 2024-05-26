/*+===================================================================
  File:      TUXER.H

  Summary:   Contains basic info for the OS. Also stores
             limine requests and responses.

  Structs:   

  Functions: getFramebuffer: Gets the framebuffer.
             getModule: Gets a module.
             getKernel: Gets the kernel.
             getFramebufferResponse: Gets the framebuffer response.
             getModuleResponse: Gets the module response.
             getKernelResponse: Gets the kernel response.
             isBaseRevisionSupported: Checks if the base revision is supported.

  Defines:   TUXER_VERSION_MAJOR: Major version.
             TUXER_VERSION_MINOR: Minor version.
             TUXER_VERSION_PATCH: Patch version.
             VERSION_CODENAME: Codename.
             VERSION_STRING: Version string.
             MODULE_INDEX_RAMFS: Index for the ramfs module.
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#ifndef TUXER_H
#define TUXER_H

#include <limine.h>
#include <kernel.h>

// VERSION INFO
#define TUXER_VERSION_MAJOR 0
#define TUXER_VERSION_MINOR 1
#define TUXER_VERSION_PATCH 0
#define VERSION_CODENAME "Jelly-Cow"
#define VERSION_STRING "0.1.0-Jelly-Cow"

// REQUEST MARKERS
__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;



// MODULE INDEXES
#define MODULE_INDEX_RAMFS 0

// GET REQUESTS
struct limine_framebuffer *getFramebuffer();
struct limine_file *getModule(int index);
struct limine_file *getKernel();

// GET RESPONSES
struct limine_framebuffer_response *getFramebufferResponse();
struct limine_module_response *getModuleResponse();
struct limine_kernel_file_response *getKernelResponse();

// CHECKS
bool isBaseRevisionSupported();

#endif // TUXER_H