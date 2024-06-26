/*
  File:         string.h  
  Description:  Contains the Definitions for the string
                implementation
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#endif // _STRING_H_