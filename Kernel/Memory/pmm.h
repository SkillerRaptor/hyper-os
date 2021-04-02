#ifndef HYPEROS_KERNEL_MEMORY_PMM_H_
#define HYPEROS_KERNEL_MEMORY_PMM_H_

#include <stddef.h>
#include <Kernel/Boot/stivale2.h>

void pmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries);

void* pmm_allocate_pages(size_t page_count);
void* pmm_callocate_pages(size_t page_count);
void pmm_free_pages(void* ptr, size_t page_count);

#endif