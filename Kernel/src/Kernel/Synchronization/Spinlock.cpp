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
	}
	
	void Spinlock::unlock()
	{
		__atomic_clear(&m_lock, __ATOMIC_RELEASE);
	}
}
