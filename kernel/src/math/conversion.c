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