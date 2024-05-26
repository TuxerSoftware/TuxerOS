/*+===================================================================
  File:      LOGGING.C

  Summary:   This file contains the implementation of the
             logger in C

  Structs:   

  Functions: ok: Logs a success message
             warn: Logs a warning message
             err: Logs an error message
             dbg: Logs a debug message

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

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