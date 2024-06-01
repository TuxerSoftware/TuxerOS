/*
  File:         defs.h
  Description:  Contains compiler specific definitions
                (GCC) in this case
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

#define comp_packed __attribute__((packed))
#define aligned(n) __attribute__((aligned(n)))
#define noret __attribute__((noreturn))

#define DIV_ROUND_UP(x, y) (x + (y - 1)) / y
#define ALIGN_UP(x, y) DIV_ROUND_UP(x, y) * y
#define ALIGN_DOWN(x, y) (x / y) *