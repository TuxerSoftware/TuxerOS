/*+===================================================================
  File:      STRING.H

  Summary:   This file contains delcerations for memory manipulation
             and string functions.

  Structs:   

  Functions: memcmp: Compares two memory blocks.
             memcpy: Copies memory.
             memmove: Moves memory.
             memset: Sets memory.

  Defines:
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#endif // _STRING_H_