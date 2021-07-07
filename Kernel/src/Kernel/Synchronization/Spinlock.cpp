/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Synchronization/Spinlock.hpp>

namespace Kernel
{
	void Spinlock::lock()
	{
		while(__atomic_test_and_set(&m_lock, __ATOMIC_ACQUIRE));
		/*
		while (!__sync_bool_compare_and_swap(&m_lock, 0, 1))
		{
			__builtin_ia32_pause();
		}
		 */
	}
	
	void Spinlock::unlock()
	{
		__atomic_clear(&m_lock, __ATOMIC_RELEASE);
		//__sync_lock_release(&m_lock);
	}
}
