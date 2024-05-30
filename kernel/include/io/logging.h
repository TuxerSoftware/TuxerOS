/*
  File:         logging.h
  Description:  Contains the Definitions for the logging
                implementation
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

void ok(const char *format, ...);
void warn(const char *format, ...);
void err(const char *format, ...);
void dbg(const char *format, ...);