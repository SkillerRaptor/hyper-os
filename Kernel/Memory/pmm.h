#ifndef HYPEROS_KERNEL_MEMORY_PMM_H_
#define HYPEROS_KERNEL_MEMORY_PMM_H_

#include <boot/stivale2.h>

#include <stddef.h>

void pmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries);
void* pmm_alloc(size_t count);
void* pmm_calloc(size_t count);
void pmm_free(void* ptr, size_t count);

#endif // HYPEROS_KERNEL_MEMORY_PMM_H_
