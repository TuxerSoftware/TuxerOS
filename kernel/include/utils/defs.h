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