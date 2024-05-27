/*+===================================================================
  File:      DEFS.H

  Summary:   This file includes compiler definitions.

  Structs:   

  Functions:

  Defines:   comp_packed: Packed attribute for structs.
             aligned: Aligned attribute for structs.
             noret: No return attribute for functions.
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

#define comp_packed __attribute__((packed))
#define aligned(n) __attribute__((aligned(n)))
#define noret __attribute__((noreturn))