/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/IoService.hpp>
#include <Kernel/Common/Logger.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	void PIC::remap(uint8_t master_offset, uint8_t slave_offset)
	{
		Logger::info("PIC: Initializing...");

		IoService::outb(s_master_command_selector, s_icw1_init | s_icw1_icw4);
		IoService::wait();
		IoService::outb(s_slave_command_selector, s_icw1_init | s_icw1_icw4);
		IoService::wait();

		IoService::outb(s_master_data_selector, master_offset);
		IoService::wait();
		IoService::outb(s_slave_data_selector, slave_offset);
		IoService::wait();

		IoService::outb(s_master_data_selector, s_master_identity);
		IoService::wait();
		IoService::outb(s_slave_data_selector, s_slave_identity);
		IoService::wait();

		IoService::outb(s_master_data_selector, s_icw1_8086);
		IoService::wait();
		IoService::outb(s_slave_data_selector, s_icw1_8086);
		IoService::wait();

		Logger::info("PIC: Initializing finished!");
	}

	void PIC::disable()
	{
		IoService::outb(s_slave_data_selector, s_disable_code);
		IoService::wait();
		IoService::outb(s_master_data_selector, s_disable_code);
	}

	void PIC::end_of_interrupt(uint8_t interrupt_request_line)
	{
		if (interrupt_request_line >= 0x8)
		{
			IoService::outb(s_slave_command_selector, s_end_interrupt_code);
		}
		IoService::outb(s_master_command_selector, s_end_interrupt_code);
	}

	void PIC::set_interrupt_request_mask(uint8_t interrupt_request_line)
	{
		uint16_t port = 0;
		uint8_t value = 0;

		if (interrupt_request_line < 0x8)
		{
			port = s_master_data_selector;
		}
		else
		{
			port = s_slave_data_selector;
			interrupt_request_line -= 0x8;
		}

		value = static_cast<uint8_t>(IoService::inb(port) | (1 << interrupt_request_line));
		IoService::outb(port, value);
	}

	void PIC::clear_interrupt_request_mask(uint8_t interrupt_request_line)
	{
		uint16_t port = 0;
		uint8_t value = 0;

		if (interrupt_request_line < 0x8)
		{
			port = s_master_data_selector;
		}
		else
		{
			port = s_slave_data_selector;
			interrupt_request_line -= 0x8;
		}

		value = static_cast<uint8_t>(IoService::inb(port) & ~(1 << interrupt_request_line));
		IoService::outb(port, value);
	}

	uint16_t PIC::service_register()
	{
		IoService::outb(s_master_command_selector, s_service_register_code);
		IoService::outb(s_slave_command_selector, s_service_register_code);
		return static_cast<uint16_t>((IoService::inb(s_slave_command_selector) << 8) | IoService::inb(s_master_command_selector));
	}

	uint16_t PIC::interrupt_request_register()
	{
		IoService::outb(s_master_command_selector, s_interrupt_request_register_code);
		IoService::outb(s_slave_command_selector, s_interrupt_request_register_code);
		return static_cast<uint16_t>((IoService::inb(s_slave_command_selector) << 8) | IoService::inb(s_master_command_selector));
	}
} // namespace Kernel
