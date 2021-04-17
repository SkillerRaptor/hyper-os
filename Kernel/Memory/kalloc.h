#ifndef HYPEROS_KERNEL_MEMORY_KALLOC_H_
#define HYPEROS_KERNEL_MEMORY_KALLOC_H_

#include <stddef.h>

void* kmalloc(size_t size);
void* kcalloc(size_t num, size_t size);
void* krealloc(void* ptr, size_t size);
void kfree(void* ptr);

#endif // HYPEROS_KERNEL_MEMORY_KALLOC_H_
