#pragma once

#include <kernel.h>

#define ASSERT(condition)                                         \
    do {                                                          \
        if (!(condition)) {                                       \
            err("Assertion failed: (%s).\n",                      \
                    #condition);                                  \
                    break;                                        \
        }                                                         \
    } while (0)
