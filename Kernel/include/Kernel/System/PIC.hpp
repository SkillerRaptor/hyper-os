/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	class PIC
	{
	public:
		static constexpr const uint8_t s_master_command_selector{ 0x20 };
		static constexpr const uint8_t s_master_data_selector{ 0x21 };
		static constexpr const uint8_t s_slave_command_selector{ 0xA0 };
		static constexpr const uint8_t s_slave_data_selector{ 0xA1 };
		
	private:
		static constexpr const uint8_t s_icw1_icw4{ 1 << 0 };
		static constexpr const uint8_t s_icw1_init{ 1 << 4 };
		static constexpr const uint8_t s_icw1_8086{ 1 << 0 };
		
		static constexpr const uint8_t s_master_identity{ 0x04 };
		static constexpr const uint8_t s_slave_identity{ 0x02 };
		
		static constexpr const uint8_t s_service_register_code{ 0x0A };
		static constexpr const uint8_t s_interrupt_request_register_code{ 0x0B };
		static constexpr const uint8_t s_disable_code{ 0xFF };
		static constexpr const uint8_t s_end_interrupt_code{ 0x20 };
		
	public:
		static void remap(uint8_t master_offset, uint8_t slave_offset);
		static void disable();
		
		static void end_of_interrupt(uint8_t interrupt_request_line);
		
		static void set_interrupt_request_mask(uint8_t interrupt_request_line);
		static void clear_interrupt_request_mask(uint8_t interrupt_request_line);
		
		static uint16_t service_register();
		static uint16_t interrupt_request_register();
	};
}
