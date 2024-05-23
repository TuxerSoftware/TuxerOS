#pragma once

#include <kernel.h>

// spins
typedef struct {
    size_t lock;
    uint8_t old_state;
} k_spinlock_t;

void lock(k_spinlock_t *lock);
void unlock(k_spinlock_t *lock);