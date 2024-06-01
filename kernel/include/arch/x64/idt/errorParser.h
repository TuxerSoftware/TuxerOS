/*
  File:         errorParser.h
  Description:  Contains the CPU exception error code parser
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

void parseError(uint64_t error_code, uint64_t vector);