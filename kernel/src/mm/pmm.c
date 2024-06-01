/*
  File:         pmm.c
  Description:  Conatins sthe Physical Memory Manager
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

uint64_t hhdm_offset;


void init_pmm(pmm_ctx_t *ctx, volatile struct limine_memmap_response *memmap,
			 volatile struct limine_hhdm_response *hhdm) {

    nullAssert(ctx);
    nullAssert(memmap);
    nullAssert(hhdm);

    hhdm_offset = hhdm->offset;
    assert(hhdm_offset != 0);

    uint64_t top_address;
	uint64_t higher_address = 0;

	for (uint64_t entryCount = 0; entryCount < memmap->entry_count;
		 entryCount++) {
		struct limine_memmap_entry *entry = memmap->entries[entryCount];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			top_address = entry->base + entry->length;
			if (top_address > higher_address)
				higher_address = top_address;
		}
	}

    ctx->bitmap_pages = higher_address / PAGE_SIZE;
	ctx->bitmap_size = ALIGN_UP(ctx->bitmap_pages / 8, PAGE_SIZE);

	for (uint64_t entryCount = 0; entryCount < memmap->entry_count;
		 entryCount++) {
		struct limine_memmap_entry *entry = memmap->entries[entryCount];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			if (entry->length >= ctx->bitmap_size) {
				ctx->bitmap = (uint8_t *)(entry->base + hhdm_offset);
				memset(ctx->bitmap, 0xFF, ctx->bitmap_size);
				entry->base += ctx->bitmap_size;
				entry->length -= ctx->bitmap_size;
				break;
			}
		}
	}

    for (uint64_t entryCount = 0; entryCount < memmap->entry_count;
		 entryCount++) {
		struct limine_memmap_entry *entry = memmap->entries[entryCount];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			for (uint64_t i = 0; i < entry->length; i += PAGE_SIZE) {
				bitmap_clear(ctx->bitmap, (entry->base + i) / PAGE_SIZE);
			}
		}
	}

	ok("PMM initialized. Bitmap at 0x%p, 0x%X pages\n", ctx->bitmap, ctx->bitmap_pages);
}

void *pmm_request_pages(pmm_ctx_t *ctx, size_t numPages) {
    uint64_t last_allocated_index = 0;

	while (1) {
		if (!bitmap_get(ctx->bitmap, last_allocated_index)) {
			size_t consecutive_free_pages = 1;

			for (size_t i = 1; i < numPages; ++i) {
				if (!bitmap_get(ctx->bitmap, last_allocated_index + i)) {
					++consecutive_free_pages;
				} else {
					consecutive_free_pages = 0;
					break;
				}
			}

			if (consecutive_free_pages == numPages) {
				for (size_t i = 0; i < numPages; ++i) {
					bitmap_set(ctx->bitmap, last_allocated_index + i);
				}

				return (void *)(last_allocated_index * PAGE_SIZE);
			}
		}

		++last_allocated_index;

		if (last_allocated_index >= ctx->bitmap_pages) {
			return NULL;
		}
	}

}
void pmm_free_pages(pmm_ctx_t *ctx, void *ptr, size_t numPages) {
    uint64_t start_bit_idx = ((uint64_t)ptr / PAGE_SIZE);

	for (size_t i = 0; i < numPages; ++i) {
		bitmap_clear(ctx->bitmap, start_bit_idx + i);
	}
}