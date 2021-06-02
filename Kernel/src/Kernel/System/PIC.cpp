#include <AK/IoService.hpp>
#include <AK/Logger.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	void PIC::remap(uint8_t master_offset, uint8_t slave_offset)
	{
		AK::Logger::info("PIC: Initializing...");
		
		AK::IoService::outb(s_master_command_selector, s_icw1_init | s_icw1_icw4);
		AK::IoService::wait();
		AK::IoService::outb(s_slave_command_selector, s_icw1_init | s_icw1_icw4);
		AK::IoService::wait();
		
		AK::IoService::outb(s_master_data_selector, master_offset);
		AK::IoService::wait();
		AK::IoService::outb(s_slave_data_selector, slave_offset);
		AK::IoService::wait();
		
		AK::IoService::outb(s_master_data_selector, s_master_identity);
		AK::IoService::wait();
		AK::IoService::outb(s_slave_data_selector, s_slave_identity);
		AK::IoService::wait();
		
		AK::IoService::outb(s_master_data_selector, s_icw1_8086);
		AK::IoService::wait();
		AK::IoService::outb(s_slave_data_selector, s_icw1_8086);
		AK::IoService::wait();
		
		AK::Logger::info("PIC: Initializing finished!");
	}
	
	void PIC::disable()
	{
		AK::IoService::outb(s_slave_data_selector, s_disable_code);
		AK::IoService::outb(s_master_data_selector, s_disable_code);
	}
	
	void PIC::send_end_of_interrupt(uint8_t interrupt_request_line)
	{
		if (interrupt_request_line >= 0x8)
		{
			AK::IoService::outb(s_slave_command_selector, s_end_interrupt_code);
		}
		AK::IoService::outb(s_master_command_selector, s_end_interrupt_code);
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
		
		value = static_cast<uint8_t>(AK::IoService::inb(port) | (1 << interrupt_request_line));
		AK::IoService::outb(port, value);
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
		
		value = static_cast<uint8_t>(AK::IoService::inb(port) & ~(1 << interrupt_request_line));
		AK::IoService::outb(port, value);
	}
	
	uint16_t PIC::service_register()
	{
		AK::IoService::outb(s_master_command_selector, s_service_register_code);
		AK::IoService::outb(s_slave_command_selector, s_service_register_code);
		return static_cast<uint16_t>((AK::IoService::inb(s_slave_command_selector) << 8) | AK::IoService::inb(s_master_command_selector));
	}
	
	uint16_t PIC::interrupt_request_register()
	{
		AK::IoService::outb(s_master_command_selector, s_interrupt_request_register_code);
		AK::IoService::outb(s_slave_command_selector, s_interrupt_request_register_code);
		return static_cast<uint16_t>((AK::IoService::inb(s_slave_command_selector) << 8) | AK::IoService::inb(s_master_command_selector));
	}
}
