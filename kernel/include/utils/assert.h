/*+===================================================================
  File:      ASSERT.H

  Summary:   Very simple assert macro.

  Structs:   

  Functions: 

  Defines:   ASSERT: Assert macro.
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

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
