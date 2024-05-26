/*+===================================================================
  File:      CONVERSION.C

  Summary:   This file contains the implementation of the
             conversion functions in C

  Structs:   

  Functions: bytesToKB: Converts bytes to kilobytes
             kbToMB: Converts kilobytes to megabytes
             kbToBytes: Converts kilobytes to bytes
             mbToKB: Converts megabytes to kilobytes

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#include <kernel.h>

double bytesToKB(double bytes) {
    return bytes / BYTE_TO_KB;
}

double kbToMB(double kilobytes) {
    return kilobytes / KB_TO_MB;
}

double kbToBytes(double kilobytes) {
    return kilobytes * BYTE_TO_KB;
}

double mbToKB(double megabytes) {
    return megabytes * KB_TO_MB;
}