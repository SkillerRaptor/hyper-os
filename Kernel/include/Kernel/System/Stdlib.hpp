#pragma once

#include <stddef.h>

namespace Kernel
{
	extern "C"
	{
		extern void* __dso_handle;
		
		void* memcpy(void* destination, const void* source, size_t num);
		void* memset(void* destination, int value, size_t num);
		void* memmove(void* destination, const void* source, size_t num);
		int memcmp(const void* first, const void* second, size_t num);
		
		char* strcpy(char* destination, const char* source);
		char* strncpy(char* destination, const char* source, size_t num);
		int strcmp(const char* first, const char* second);
		int strncmp(const char* first, const char* second, size_t num);
		size_t strlen(const char* string);
		
		void __stack_chk_fail() __attribute__((used));
		void __stack_chk_fail_local() __attribute__((used));
		int __cxa_atexit(void (* destructor)(void*), void* object_ptr, void* dso) __attribute__((used));
		void __cxa_pure_virtual() __attribute__((used));
	}
}
