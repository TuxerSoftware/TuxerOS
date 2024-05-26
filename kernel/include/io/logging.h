/*+===================================================================
  File:      LOGGING.H

  Summary:   This file is the header file for logging functions.

  Structs:   

  Functions: ok: Logs an OK message.
             warn: Logs a warning message.
             err: Logs an error message.
             dbg: Logs a debug message.

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

void ok(const char *format, ...);
void warn(const char *format, ...);
void err(const char *format, ...);
void dbg(const char *format, ...);