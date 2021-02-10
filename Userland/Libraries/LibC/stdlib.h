#pragma once

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

void abort() __NORETURN;

void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

__END_DECLS

void* operator new(size_t size);
void* operator new[](size_t size);
void* operator new(size_t, void* ptr);
void* operator new[](size_t, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);
void operator delete(void* ptr, size_t);
void operator delete[](void* ptr, size_t);