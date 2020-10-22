#pragma once

#include <LibC/sys/cdefs.h>
#include <LibC/sys/types.h>

__BEGIN_DECLS

int memcmp(const void* ptr1, const void* ptr2, size_t num);
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
void* memset(void* ptr, int value, size_t num);

size_t strlen(const char* str);

__END_DECLS