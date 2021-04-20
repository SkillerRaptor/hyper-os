#ifndef HYPEROS_KERNEL_SYNCHRONIZATION_SPINLOCK_H_
#define HYPEROS_KERNEL_SYNCHRONIZATION_SPINLOCK_H_

#include <stdint.h>

typedef volatile uint32_t spinlock;

void spinlock_lock(spinlock* lock);
void spinlock_unlock(spinlock* lock);

#endif // HYPEROS_KERNEL_SYNCHRONIZATION_SPINLOCK_H_
