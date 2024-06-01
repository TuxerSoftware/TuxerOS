/*
  File:         binutils.h  
  Description:  Contains some basic binary utilities
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

uint8_t getBit(uint64_t num, uint64_t bit);

void setBit(uint64_t *num, uint64_t bit);