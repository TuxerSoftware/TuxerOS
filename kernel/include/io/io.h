/*
  File:         io.c
  Description:  Contains I/O functions
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#pragma once

#include <kernel.h>

void outb(uint16_t port, uint8_t value); // Write a byte to a port
uint8_t inb(uint16_t port); // Read a byte from a port

void outw(uint16_t port, uint16_t value); // Write a word to a port
uint16_t inw(uint16_t port); // Read a word from a port

void inbm(uint16_t port, uint16_t *addr, size_t count); // Reads a byte from a port and puts it into memory