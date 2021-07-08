/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Drivers/HPET.hpp>
#include <Kernel/Interrupts/APIC.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/Interrupts/PIC.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/MADT.hpp>

namespace Kernel
{
	void APIC::initialize()
	{
		Logger::info("APIC: Initializing...");

		PIC::disable();

		for (size_t i = 0; i < MADT::ioapics().size(); ++i)
		{
			io_apic_mask_all_gsi(i);
		}

		bool mapped_irqs[16] = { false };
		for (size_t i = 0; i < MADT::isos().size(); ++i)
		{
			MADT::ISO* iso = MADT::isos()[i];
			ssize_t io_apic = io_apic_from_redirect(iso->global_system_interrupt);
			if (io_apic == -1)
			{
				continue;
			}

			io_apic_redirect_gsi(io_apic, iso->irq_source + 32, iso->global_system_interrupt, iso->flags, true);
			if (iso->global_system_interrupt < 16)
			{
				mapped_irqs[io_apic] = true;
			}
		}

		for (size_t i = 0; i < 16; ++i)
		{
			if (!mapped_irqs[i])
			{
				ssize_t io_apic = io_apic_from_redirect(i);
				if (io_apic == -1)
				{
					continue;
				}

				io_apic_redirect_gsi(io_apic, i + 32, i, 0, true);
			}
		}

		ssize_t io_apic = io_apic_from_redirect(2);
		if (io_apic != -1)
		{
			io_apic_mask_gsi(io_apic, 2);
		}

		IDT::set_handler(0xFF, IDT::HandlerType::Present | IDT::HandlerType::InterruptGate, APIC::lapic_spur_handler);

		uint32_t spurious_interrupt = lapic_read(s_spurious_interrupt_vector_register);
		lapic_write(s_spurious_interrupt_vector_register, spurious_interrupt | (1 << 8) | 0xFF);

		Logger::info("APIC: Initializing finished!");
	}

	void APIC::calibrate(uint64_t ms)
	{
		lapic_write(s_divide_configuration_register, 0x3);
		lapic_write(s_initial_count_register, ~0);

		HPET::sleep(ms);

		uint32_t ticks = ~0 - lapic_read(s_current_count_register);

		lapic_write(s_lvt_timer_register, 32 | 0x20000);
		lapic_write(s_divide_configuration_register, 0x3);
		lapic_write(s_initial_count_register, ticks);
	}

	void APIC::lapic_end_of_interrupt()
	{
		APIC::lapic_write(0xB0, 0);
	}

	void APIC::lapic_write(uint32_t reg, uint32_t data)
	{
		auto* lapic_base = reinterpret_cast<__volatile__ uint32_t*>((CPU::read_msr(s_ia32_apic_base_msr) & 0xFFFFF000) + Memory::s_physical_memory_offset + reg);
		*lapic_base = data;
	}

	uint32_t APIC::lapic_read(uint32_t reg)
	{
		auto lapic_base = *reinterpret_cast<__volatile__ uint32_t*>((CPU::read_msr(s_ia32_apic_base_msr) & 0xFFFFF000) + Memory::s_physical_memory_offset + reg);
		if (lapic_base == s_lapic_id_register)
		{
			return lapic_base >> 24;
		}
		return lapic_base;
	}

	void APIC::lapic_spur_handler(Registers*)
	{
		lapic_end_of_interrupt();
	}

	void APIC::io_apic_redirect_gsi(size_t lapic, uint8_t vector, uint32_t gsi, uint16_t flags, bool status)
	{
		size_t redirect = vector;

		if (flags & (1 << 1))
		{
			redirect |= 1 << 13;
		}

		if (flags & (1 << 3))
		{
			redirect |= 1 << 15;
		}

		if (!status)
		{
			redirect |= 1 << 16;
		}

		redirect |= (static_cast<uint64_t>(lapic)) << 56;

		size_t io_apic = io_apic_from_redirect(gsi);
		io_apic_write_redirection(io_apic, gsi, redirect);
	}

	ssize_t APIC::io_apic_from_redirect(uint32_t gsi)
	{
		for (size_t i = 0; i < MADT::ioapics().size(); ++i)
		{
			uint32_t gsi_base = MADT::ioapics()[i]->global_system_interrupt_base;
			if (gsi_base <= gsi && gsi_base + io_apic_max_gsi(i) >= gsi)
			{
				return static_cast<ssize_t>(i);
			}
		}

		return -1;
	}

	void APIC::io_apic_mask_all_gsi(size_t io_apic)
	{
		for (uint32_t i = MADT::ioapics()[io_apic]->global_system_interrupt_base; i < io_apic_max_gsi(io_apic); ++i)
		{
			io_apic_mask_gsi(io_apic, i);
		}
	}

	void APIC::io_apic_unmask_all_gsi(size_t io_apic)
	{
		for (uint32_t i = MADT::ioapics()[io_apic]->global_system_interrupt_base; i < io_apic_max_gsi(io_apic); ++i)
		{
			io_apic_unmask_gsi(io_apic, i);
		}
	}

	void APIC::io_apic_mask_gsi(size_t io_apic, uint32_t gsi)
	{
		io_apic_write_redirection(io_apic, gsi, io_apic_read_redirection(io_apic, gsi) | (1 << 16));
	}

	void APIC::io_apic_unmask_gsi(size_t io_apic, uint32_t gsi)
	{
		io_apic_write_redirection(io_apic, gsi, io_apic_read_redirection(io_apic, gsi) & (1 << 16));
	}

	uint32_t APIC::io_apic_max_gsi(size_t io_apic)
	{
		uint32_t data = io_apic_read(io_apic, 1) >> 16;
		return data & ~(1 << 7);
	}

	void APIC::io_apic_write_redirection(size_t io_apic, uint32_t gsi, uint64_t data)
	{
		uint32_t reg = (gsi - MADT::ioapics()[io_apic]->global_system_interrupt_base) * 2 + 16;
		io_apic_write(io_apic, reg + 0, static_cast<uint32_t>(data));
		io_apic_write(io_apic, reg + 1, static_cast<uint32_t>(data >> 32));
	}

	uint64_t APIC::io_apic_read_redirection(size_t io_apic, uint32_t gsi)
	{
		uint32_t reg = (gsi - MADT::ioapics()[io_apic]->global_system_interrupt_base) * 2 + 16;
		return io_apic_read(io_apic, reg) | (static_cast<uint64_t>(io_apic_read(io_apic, reg + 1)) << 32);
	}

	void APIC::io_apic_write(size_t io_apic, uint32_t reg, uint32_t data)
	{
		__volatile__ uint32_t* base = io_apic_get_base(io_apic);
		*(base + 0) = reg;
		*(base + 4) = data;
	}

	uint32_t APIC::io_apic_read(size_t io_apic, uint32_t reg)
	{
		__volatile__ uint32_t* base = io_apic_get_base(io_apic);
		*(base + 0) = reg;
		return *(base + 4);
	}

	__volatile__ uint32_t* APIC::io_apic_get_base(size_t io_apic)
	{
		return reinterpret_cast<__volatile__ uint32_t*>(static_cast<uint64_t>(MADT::ioapics()[io_apic]->address) + Memory::s_physical_memory_offset);
	}
} // namespace Kernel
