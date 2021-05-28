#ifndef HYPEROS_KERNEL_MEMORY_VMM_H_
#define HYPEROS_KERNEL_MEMORY_VMM_H_

#include <boot/stivale2.h>
#include <synchronization/spinlock.h>

#include <stddef.h>

struct pagemap
{
	uintptr_t top_level;
	spinlock lock;
	uint8_t zero[4];
};

void vmm_init(struct stivale2_mmap_entry* memory_map, size_t memory_map_entries);

struct pagemap* vmm_create_new_pagemap(void);
void vmm_switch_pagemap(struct pagemap* pagemap);
uint8_t vmm_map_page(struct pagemap* pagemap, uintptr_t virtual_address, uintptr_t physical_address, uintptr_t flags);

#endif // HYPEROS_KERNEL_MEMORY_VMM_H_
