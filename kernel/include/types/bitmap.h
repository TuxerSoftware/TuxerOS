/*
  File:         birmap.h
  Description:  Conatins some basic bitmap functions
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

typedef uint8_t* bitmap_t;

void bitmap_set(bitmap_t bitmap, uint64_t bit);
void bitmap_clear(bitmap_t bitmap, uint64_t bit);
bool bitmap_get(bitmap_t bitmap, uint64_t bit);

