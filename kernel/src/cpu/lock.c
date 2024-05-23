#include <kernel.h>

void lock(k_spinlock_t *lock) {
    // could use cas here to store taking task ptr, for now tas does the job
    // only sets the first byte at ptr
    size_t c = 0;
    while (__atomic_test_and_set(&lock->lock, __ATOMIC_ACQUIRE)) {
        if (++c > 10000000ul) err("DEADLOCK at %p\n", &lock->lock);
    }
}

void unlock(k_spinlock_t *lock) {
    __atomic_store_n(&lock->lock, 0, __ATOMIC_RELEASE);
}