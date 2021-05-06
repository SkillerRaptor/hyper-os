#ifndef HYPEROS_KERNEL_MEMORY_KALLOC_H_
#define HYPEROS_KERNEL_MEMORY_KALLOC_H_

#include <stddef.h>

void* kmalloc(size_t size);
void* kcalloc(size_t element_count, size_t size);
void* krealloc(void* pointer, size_t size);
void kfree(void* pointer);

#endif // HYPEROS_KERNEL_MEMORY_KALLOC_H_
