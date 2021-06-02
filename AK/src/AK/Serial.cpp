#include <AK/IoService.hpp>
#include <AK/Serial.hpp>

namespace AK
{
	void Serial::initialize()
	{
		IoService::outb(s_serial_port + 1, 0x00);
		IoService::outb(s_serial_port + 3, 0x80);
		IoService::outb(s_serial_port + 0, 0x03);
		IoService::outb(s_serial_port + 1, 0x00);
		IoService::outb(s_serial_port + 3, 0x03);
		IoService::outb(s_serial_port + 2, 0xC7);
		IoService::outb(s_serial_port + 4, 0x0B);
		IoService::outb(s_serial_port + 4, 0x1E);
		IoService::outb(s_serial_port + 0, 0xAE);
		
		if (IoService::inb(s_serial_port + 0) != 0xAE)
		{
			return;
		}
		
		IoService::outb(s_serial_port + 4, 0x0F);
	}
	
	bool Serial::transmit_empty()
	{
		return IoService::inb(s_serial_port + 5) & 0x20;
	}
	
	void Serial::write(char c)
	{
		while (Serial::transmit_empty() == 0);
		
		IoService::outb(s_serial_port, c);
	}
	
	void Serial::write(const char* string)
	{
		while (*string)
		{
			Serial::write(*(string++));
		}
	}
	
	void Serial::write(const StringView& string)
	{
		for (const char c : string)
		{
			Serial::write(c);
		}
	}
	
	void Serial::write(const String& string)
	{
		for (const char c : string)
		{
			Serial::write(c);
		}
	}
}
