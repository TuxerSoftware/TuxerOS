/*
  File:         birmap.c
  Description:  Conatins some basic bitmap functions
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

void bitmap_set(bitmap_t bitmap, uint64_t bit)
{
	bitmap[bit / 8] |= 1 << (bit % 8);
}

void bitmap_clear(bitmap_t bitmap, uint64_t bit)
{
	bitmap[bit / 8] &= ~(1 << (bit % 8));
}

bool bitmap_get(bitmap_t bitmap, uint64_t bit)
{
	return (bitmap[bit / 8] & (1 << (bit % 8))) != 0;
}