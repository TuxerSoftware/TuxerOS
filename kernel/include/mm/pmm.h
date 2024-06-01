/*
  File:         pmm.h
  Description:  Conatins sthe Physical Memory Manager
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

typedef struct pmm_ctx {
    bitmap_t bitmap;
    uint64_t bitmap_pages;
    uint64_t bitmap_size;
} pmm_ctx_t;

#define PAGE_SIZE 4096

extern uint64_t hhdm_offset;

#define HIGHER_HALF(ptr) ((void *)((uint64_t)ptr) + hhdm_offset)
#define PHYSICAL(ptr) ((void *)((uint64_t)ptr) - hhdm_offset)

void init_pmm(pmm_ctx_t *ctx, volatile struct limine_memmap_response *memmap,
			 volatile struct limine_hhdm_response *hhdm);

void *pmm_request_pages(pmm_ctx_t *ctx, size_t numPages);
void pmm_free_pages(pmm_ctx_t *ctx, void *ptr, size_t numPages);


