/*
  File:         lock.h
  Description:  Contains the definitions for the CPU
                lock routines
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/
#pragma once

#include <kernel.h>

// spins
typedef struct {
    size_t lock;
    uint8_t old_state;
} k_spinlock_t;

void spin_lock(k_spinlock_t *lock);
void spin_unlock(k_spinlock_t *lock);