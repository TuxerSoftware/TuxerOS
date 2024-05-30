/*
  File:         panic.h
  Description:  Contains the definitions for the panic
                routines
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

void panic(idt_frame_t frame, int backupErrorCode ,const char* message, ...);