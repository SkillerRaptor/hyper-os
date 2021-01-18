#pragma once

#include <LibC/stddef.h>
#include <LibC/sys/cdefs.h>
#include <LibC/sys/types.h>

__BEGIN_DECLS

void abort() __NORETURN;

void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

inline void* operator new(size_t size)
{
	return malloc(size);
}

inline void* operator new[](size_t size)
{
	return malloc(size);
}

inline void operator delete(void* ptr)
{
	free(ptr);
}

inline void operator delete[](void* ptr)
{
	free(ptr);
}

inline void operator delete(void* ptr, size_t)
{
	free(ptr);
}

inline void operator delete[](void* ptr, size_t)
{
	free(ptr);
}

__END_DECLS