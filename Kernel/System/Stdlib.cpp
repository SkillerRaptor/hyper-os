#include <AK/Assertion.hpp>
#include <AK/Logger.hpp>
#include <Kernel/System/Stdlib.hpp>

namespace Kernel
{
	void* __dso_handle __attribute__((visibility("hidden")));
	
	atexit_func_entry_t __atexit_funcs[s_atexit_max_functions];
	uarch_t __atexit_func_count = 0;
	
	void* memcpy(void* destination, const void* source, size_t num)
	{
		auto* _destination = reinterpret_cast<uint8_t*>(destination);
		const auto* _source = reinterpret_cast<const uint8_t*>(source);
		
		for (size_t i = 0; i < num; i++)
		{
			asm volatile ("nop");
			_destination[i] = _source[i];
		}
		
		return destination;
	}
	
	void* memset(void* destination, int value, size_t num)
	{
		auto* _destination = reinterpret_cast<uint8_t*>(destination);
		
		for (size_t i = 0; i < num; i++)
		{
			asm volatile ("nop");
			_destination[i] = static_cast<uint8_t>(value);
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
				asm volatile ("nop");
				_destination[i] = _source[i];
			}
		}
		else if (source < destination)
		{
			for (size_t i = num; i > 0; i--)
			{
				asm volatile ("nop");
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
				asm volatile ("nop");
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
			asm volatile ("nop");
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
			asm volatile ("nop");
			destination[i] = source[i];
		}
		for (; i < num; i++)
		{
			asm volatile ("nop");
			destination[i] = 0;
		}
		
		return destination;
	}
	
	int strcmp(const char* first, const char* second)
	{
		for (size_t i = 0;; i++)
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
		AK::Logger::error("__stack_chk_fail");
		VERIFY_NOT_REACHED();
	}
	
	void __stack_chk_fail_local()
	{
		AK::Logger::error("__stack_chk_fail_local");
		VERIFY_NOT_REACHED();
	}
	
	int __cxa_atexit(void (* destructor_function)(void*), void* object_pointer, void* dso_handle)
	{
		if (__atexit_func_count >= s_atexit_max_functions)
		{
			return -1;
		}
		
		__atexit_funcs[__atexit_func_count].destructor_function = destructor_function;
		__atexit_funcs[__atexit_func_count].object_ptr = object_pointer;
		__atexit_funcs[__atexit_func_count].dso_handle = dso_handle;
		__atexit_func_count++;
		return 0;
	}
	
	void __cxa_pure_virtual()
	{
		AK::Logger::error("__cxa_pure_virtual");
		VERIFY_NOT_REACHED();
	}
}
