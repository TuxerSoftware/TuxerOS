/*+===================================================================
  File:      CONVERSIONS.H

  Summary:   This file has the declerations for some
             conversion utilities.

  Structs:   

  Functions: bytesToKB: Converts bytes to kilobytes.
             kbToMB: Converts kilobytes to megabytes.
             kbToBytes: Converts kilobytes to bytes.
             mbToKB: Converts megabytes to kilobytes.

 Defines:   BYTE_TO_KB: The number of bytes in a kilobyte.
            KB_TO_MB: The number of kilobytes in a megabyte.
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

#define BYTE_TO_KB 1024.0
#define KB_TO_MB 1024.0

double bytesToKB(double bytes);
double kbToMB(double kilobytes);
double kbToBytes(double kilobytes);
double mbToKB(double megabytes);