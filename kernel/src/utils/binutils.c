/*
  File:         binutils.h  
  Description:  Contains some basic binary utilities
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

uint8_t getBit(uint64_t num, uint64_t bit) {
    return (num >> bit) & 1;
}

void setBit(uint64_t *num, uint64_t bit) {
    *num |= (1ULL << bit);
}

uint64_t getBits(uint64_t num, uint64_t start, uint64_t count) {
    if (start >= 64 || count == 0 || start + count > 64) {
        return 0; // or handle the error as appropriate for your use case
    }
    // Create a mask with 'count' bits set to 1
    uint64_t mask = (1ULL << count) - 1;
    // Shift the mask to the correct position and apply it to the number
    return (num >> start) & mask;
}