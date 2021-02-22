#ifndef HYPEROS_USERLAND_LIBARIRES_LIBC_STDLIB_H_
#define HYPEROS_USERLAND_LIBARIRES_LIBC_STDLIB_H_

#include <stddef.h>
#include <sys/cdefs.h>

void abort() __NORETURN;

void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#endif