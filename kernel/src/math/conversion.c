#include <kernel.h>

int bytesToKB(int bytes) {
    return bytes / BYTE_TO_KB;
}

int kbToMB(int kilobytes) {
    return kilobytes / KB_TO_MB;
}

int kbToBytes(int kilobytes) {
    return kilobytes * BYTE_TO_KB;
}

int mbToKB(int megabytes) {
    return megabytes * KB_TO_MB;
}