#pragma once

#include <kernel.h>

#define BYTE_TO_KB 1024.0
#define KB_TO_MB 1024.0

double bytesToKB(double bytes);
double kbToMB(double kilobytes);
double kbToBytes(double kilobytes);
double mbToKB(double megabytes);