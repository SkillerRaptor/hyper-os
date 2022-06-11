/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "scheduling/spinlock.h"

void spinlock_lock(struct spinlock *spinlock)
{
	while (__atomic_test_and_set(&spinlock->lock, __ATOMIC_ACQUIRE))
		;
}

void spinlock_unlock(struct spinlock *spinlock)
{
	__atomic_clear(&spinlock->lock, __ATOMIC_RELEASE);
}
