/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel
{
	class APIC
	{
	public:
		static void initialize();
		
		static void lapic_end_of_interrupt();
		
		static void lapic_write(uint32_t reg, uint32_t data);
		static uint32_t lapic_read(uint32_t reg);
		
	private:
		static uintptr_t lapic_get_mmio_base();
	};
}
