#include <kernel.h>

PMBR_t* getPMBR() {
    PMBR_t mbr;
    ata_read(0, (uint8_t *)&mbr, 1);
    return &mbr;
}
GPTPartTable_t getGPTPartTable() {
    GPTPartTable_t gpt;
    ata_read(1, (uint8_t *)&gpt, 1);
    return gpt;
}
GPTPartEntry_t getGPTPartEntry(uint32_t index) {
    GPTPartEntry_t entry;
    GPTPartTable_t gpt = getGPTPartTable();
    if (index >= gpt.header.num_part_entries) {
        return entry;
    }
    ata_read(gpt.header.part_entry_lba + index, (uint8_t *)&entry, 1);
    return entry;
}