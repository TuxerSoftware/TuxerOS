/*
  File:         lock.c
  Description:  Contains the implementation for the CPU
                lock routines
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/
#include <kernel.h>

void spin_lock(k_spinlock_t *lock) {
    size_t c = 0;
    while (__atomic_test_and_set(&lock->lock, __ATOMIC_ACQUIRE)) {
        if (++c > 10000000ul) err("DEADLOCK at %p\n", &lock->lock);
    }
}

void spin_unlock(k_spinlock_t *lock) {
    __atomic_store_n(&lock->lock, 0, __ATOMIC_RELEASE);
}