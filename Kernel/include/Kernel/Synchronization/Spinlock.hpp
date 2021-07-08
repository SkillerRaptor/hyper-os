/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	class Spinlock
	{
	public:
		void lock();
		void unlock();

	private:
		volatile uint32_t m_lock;
	};
} // namespace Kernel
