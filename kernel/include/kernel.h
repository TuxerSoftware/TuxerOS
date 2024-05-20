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
