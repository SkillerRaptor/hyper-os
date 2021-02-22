#ifndef HYPEROS_USERLAND_LIBRARIES_LIBC_STRING_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBC_STRING_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

/* Copying */
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t num);

/* Concatenation */
char* strcat(char* dest, const char* src);

/* Comparison */
int memcmp(const void* ptr1, const void* ptr2, size_t num);

/* Other */
void* memset(void* ptr, int value, size_t num);
size_t strlen(const char* str);

#endif