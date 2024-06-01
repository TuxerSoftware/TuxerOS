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