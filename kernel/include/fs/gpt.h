#pragma once

#include <kernel.h>

#define GPT_SIGNATURE 0x5452415020494645

typedef struct PMBR {
    uint8_t boot_indicator;
    uint8_t starting_head;
    uint16_t starting_sector_cylinder;
    uint8_t system_id;
    uint8_t ending_head;
    uint16_t ending_sector_cylinder;
    uint32_t starting_lba;
    uint32_t ending_lba;
} PMBR_t;

typedef struct GPTPartTableHeader {
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t header_crc32;
    uint32_t reserved;
    uint64_t header_lba;
    uint64_t backup_header_lba;
    uint64_t first_usable_lba;
    uint64_t last_usable_lba;
    uint8_t disk_guid[16];
    uint64_t part_entry_lba;
    uint32_t num_part_entries;
    uint32_t size_part_entries;
    uint32_t part_entries_crc32;
    uint8_t reserved2[420]; // nice
} GPTPartTableHeader_t;

typedef struct GPTPartEntry {
    uint8_t part_type_guid[16];
    uint8_t part_guid[16];
    uint64_t first_lba;
    uint64_t last_lba;
    uint64_t flags;
    uint8_t part_name[72];
} GPTPartEntry_t;

typedef struct GPTPartTable {
    GPTPartTableHeader_t header;
    GPTPartEntry_t entries[];
} GPTPartTable_t;

PMBR_t *getPMBR();
GPTPartTable_t getGPTPartTable();
GPTPartEntry_t getGPTPartEntry(uint32_t index);