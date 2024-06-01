/*
  File:         assert.h  
  Description:  Contains the assert() macro
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/
#pragma once

#include <kernel.h>

#define assert(condition)                                                                     \
    do {                                                                                      \
        if (!(condition)) {                                                                   \
            err("Assertion failed at %s:%d in function %s!\n", __FILE__, __LINE__, __func__); \
        }                                                                                     \
    } while (0)

#define nullAssert(obj)                         \
    do {                                        \
        if (obj == NULL) {                       \
            err("Null assertion failed at %s:%d in function %s!\n", __FILE__, __LINE__, __func__); \
        }                                       \
    } while (0)
