#ifndef HYPEROS_KERNEL_LIB_BUILTINS_H_
#define HYPEROS_KERNEL_LIB_BUILTINS_H_

#include <stddef.h>

void* memcpy(void* destination, const void* source, size_t n);
void* memset(void* destination, int value, size_t n);
void* memmove(void* destination, const void* source, size_t n);
int memcmp(const void* first, const void* second, size_t n);

char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t n);
int strcmp(const char* first, const char* second);
int strncmp(const char* first, const char* second, size_t n);
size_t strlen(const char* string);

#endif // HYPEROS_KERNEL_LIB_BUILTINS_H_
