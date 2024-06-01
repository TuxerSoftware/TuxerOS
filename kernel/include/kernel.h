/*
  File:         kernel.h
  Description:  Conatins all header so I only need to include
                this file in the source files
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#include "std/stdasm.h"
#include "sys/tuxer.h"
#include "std/string.h"
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
#include "utils/panic.h"
#include "types/bitmap.h"
#include "mm/pmm.h"

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
