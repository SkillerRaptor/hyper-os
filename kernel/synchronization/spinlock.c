#include "spinlock.h"

void spinlock_lock(spinlock* lock)
{
	while (!__sync_bool_compare_and_swap(lock, 0, 1))
	{
		__builtin_ia32_pause();
	}
}

void spinlock_unlock(spinlock* lock)
{
	__sync_lock_release(lock);
}
