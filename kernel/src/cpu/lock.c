/*+===================================================================
  File:      LOCK.C

  Summary:   This file contains the implementation of CPI
             locks in C

  Structs:   

  Functions: spin_lock: Locks a spinlock
             spin_unlock: Unlocks a spinlock

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#include <kernel.h>

void spin_lock(k_spinlock_t *lock) {
    // could use cas here to store taking task ptr, for now tas does the job
    // only sets the first byte at ptr
    size_t c = 0;
    while (__atomic_test_and_set(&lock->lock, __ATOMIC_ACQUIRE)) {
        if (++c > 10000000ul) err("DEADLOCK at %p\n", &lock->lock);
    }
}

void spin_unlock(k_spinlock_t *lock) {
    __atomic_store_n(&lock->lock, 0, __ATOMIC_RELEASE);
}