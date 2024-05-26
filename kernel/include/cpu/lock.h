/*+===================================================================
  File:      LOCK.H

  Summary:   This file contains some CPU locking primitives,
             using GCC atomic builtins.

  Structs:   k_spinlock_t: Structure for a spinlock.

  Functions: spin_lock: Locks a spinlock.
             spin_unlock: Unlocks a spinlock.

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

// spins
typedef struct {
    size_t lock;
    uint8_t old_state;
} k_spinlock_t;

void spin_lock(k_spinlock_t *lock);
void spin_unlock(k_spinlock_t *lock);