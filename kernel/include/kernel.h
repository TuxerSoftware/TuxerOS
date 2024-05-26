/*+===================================================================
  File:      KERNEL.H

  Summary:   This file includes common types and all header,
             so I can only include this file.

  Structs:   

  Functions: 

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#include "std/stdasm.h"
#include "sys/tuxer.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "std/stdio.h"
#include "io/logging.h"
#include "math/conversion.h"
#include "cpu/cpu.h"
#include "utils/defs.h"
#include "arch/x64/gdt.h"
#include "cpu/lock.h"
#include "arch/x64/idt/idt.h"
#include "utils/assert.h"

typedef double f64;
typedef float f32;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef u8 byte;
typedef u16 word;
typedef u32 dword;
typedef u64 qword;
