/*
  File:         assert.h  
  Description:  Contains the assert() macro
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/
#pragma once

#include <kernel.h>

#define ASSERT(condition)                                         \
    do {                                                          \
        if (!(condition)) {                                       \
            err("Assertion failed: (%s). File: %s, Line: %d\n",   \
                    #condition, __FILE__ ,__LINE__);              \
                    break;                                        \
        }                                                         \
    } while (0)
