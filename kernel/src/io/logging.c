/*
  File:         logging.c
  Description:  Contains the implementation for the logging
                routines
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

void ok(const char *format, ...) {
    printf("[\e[32m  OK  \e[0m] ");
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}
void warn(const char *format, ...) {
    printf("[\e[33m WARN \e[0m] ");
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}
void err(const char *format, ...) {
    printf("[\e[31mFAILED\e[0m] ");
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}

void dbg(const char *format, ...) {
    printf("[\e[35mDEBUG \e[0m] ");
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}