/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>

struct spinlock
{
	volatile uint32_t lock;
};

void spinlock_lock(struct spinlock *spinlock);
void spinlock_unlock(struct spinlock *spinlock);
