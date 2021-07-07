/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Registers.hpp>
#include <Kernel/Common/Types.hpp>
#include <stddef.h>

namespace Kernel
{
	class APIC
	{
	public:
		static void initialize();

		static void calibrate(uint64_t ms);

		static void lapic_end_of_interrupt();

		static void lapic_write(uint32_t reg, uint32_t data);
		static uint32_t lapic_read(uint32_t reg);

		static void io_apic_redirect_gsi(size_t lapic, uint8_t vector, uint32_t gsi, uint16_t flags, bool status);
		static void io_apic_redirect_irq(size_t lapic, uint8_t vector, uint32_t irq, bool status);
		static ssize_t io_apic_from_redirect(uint32_t gsi);

		static void io_apic_mask_all_gsi(size_t io_apic);
		static void io_apic_mask_gsi(size_t io_apic, uint32_t gsi);
		static void io_apic_unmask_gsi(size_t io_apic, uint32_t gsi);

		static uint32_t io_apic_max_gsi(size_t io_apic);

		static void io_apic_write_redirection(size_t io_apic, uint32_t gsi, uint64_t data);
		static uint64_t io_apic_read_redirection(size_t io_apic, uint32_t gsi);

		static void io_apic_write(size_t io_apic, uint32_t reg, uint32_t data);
		static uint32_t io_apic_read(size_t io_apic, uint32_t reg);

	private:
		static void lapic_spur_handler(Registers*);

		static __volatile__ uint32_t* lapic_get_mmio_base();
		static __volatile__ uint32_t* ioapic_get_base(size_t io_apic);
	};
} // namespace Kernel
