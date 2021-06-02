#include <AK/Assertion.hpp>
#include <Kernel/System/Stdlib.hpp>
#include <stdint.h>

namespace Kernel
{
	void* memcpy(void* destination, const void* source, size_t num)
	{
		auto* _destination = reinterpret_cast<uint8_t*>(destination);
		const auto* _source = reinterpret_cast<const uint8_t*>(source);
		
		for (size_t i = 0; i < num; i++)
		{
			_destination[i] = _source[i];
		}
		
		return destination;
	}
	
	void* memset(void* destination, int value, size_t num)
	{
		auto* _destination = reinterpret_cast<uint8_t*>(destination);
		
		for (size_t i = 0; i < num; i++)
		{
			_destination[i] = (uint8_t) value;
		}
		
		return destination;
	}
	
	void* memmove(void* destination, const void* source, size_t num)
	{
		auto* _destination = reinterpret_cast<uint8_t*>(destination);
		const auto* _source = reinterpret_cast<const uint8_t*>(source);
		
		if (source > destination)
		{
			for (size_t i = 0; i < num; i++)
			{
				_destination[i] = _source[i];
			}
		}
		else if (source < destination)
		{
			for (size_t i = num; i > 0; i--)
			{
				_destination[i - 1] = _source[i - 1];
			}
		}
		
		return destination;
	}
	
	int memcmp(const void* first, const void* second, size_t num)
	{
		const auto* _first = reinterpret_cast<const uint8_t*>(first);
		const auto* _second = reinterpret_cast<const uint8_t*>(second);
		
		for (size_t i = 0; i < num; i++)
		{
			if (_first[i] != _second[i])
			{
				return _first[i] < _second[i] ? -1 : 1;
			}
		}
		
		return 0;
	}
	
	char* strcpy(char* destination, const char* source)
	{
		size_t i;
		
		for (i = 0; source[i]; i++)
		{
			destination[i] = source[i];
		}
		destination[i] = 0;
		
		return destination;
	}
	
	char* strncpy(char* destination, const char* source, size_t num)
	{
		size_t i;
		
		for (i = 0; i < num && source[i]; i++)
		{
			destination[i] = source[i];
		}
		for (; i < num; i++)
		{
			destination[i] = 0;
		}
		
		return destination;
	}
	
	int strcmp(const char* first, const char* second)
	{
		for (size_t i = 0; ; i++)
		{
			char first_char = first[i];
			char second_char = second[i];
			if (first_char != second_char)
			{
				return first_char - second_char;
			}
			if (!first_char)
			{
				return 0;
			}
		}
	}
	
	int strncmp(const char* first, const char* second, size_t num)
	{
		for (size_t i = 0; i < num; i++)
		{
			char first_char = first[i];
			char second_char = second[i];
			if (first_char != second_char)
			{
				return first_char - second_char;
			}
			if (!first_char)
			{
				return 0;
			}
		}
		
		return 0;
	}
	
	size_t strlen(const char* string)
	{
		size_t length;
		for (length = 0; string[length]; length++);
		return length;
	}
	
	void __stack_chk_fail()
	{
		VERIFY_NOT_REACHED();
	}
	
	void __stack_chk_fail_local()
	{
		VERIFY_NOT_REACHED();
	}
	
	int __cxa_atexit(void (* destructor)(void*), void* arg, void* dso)
	{
		VERIFY_NOT_REACHED();
		return 0;
	}
	
	void __cxa_pure_virtual()
	{
		VERIFY_NOT_REACHED();
	}
}
