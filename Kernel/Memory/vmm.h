#ifndef HYPEROS_KERNEL_MEMORY_VMM_H_
#define HYPEROS_KERNEL_MEMORY_VMM_H_

#include <stddef.h>
#include <Kernel/Boot/stivale2.h>

enum
{
    PAGEMAP_ATTRIBUTE_PRESENT = 1 << 0,
    PAGEMAP_ATTRIBUTE_READ_AND_WRITE = 1 << 1,
    PAGEMAP_ATTRIBUTE_USER_SUPERVISOR = 1 << 2,
    PAGEMAP_ATTRIBUTE_WRITE_TROUGH = 1 << 3,
    PAGEMAP_ATTRIBUTE_CACHE_DISABLED = 1 << 4,
    PAGEMAP_ATTRIBUTE_ACCESSED = 1 << 5,
    PAGEMAP_ATTRIBUTE_SIZE_4KB = 1 << 7
};

typedef struct
{
    uintptr_t* top_level;
} pagemap_t;

void vmm_init(struct stivale2_mmap_entry* memory_map, size_t memory_map_entries);

pagemap_t* vmm_create_new_pagemap(void);
void vmm_switch_pagemap(pagemap_t* pagemap);
void vmm_map_page(pagemap_t* pagemap, void* physical_address, void* virtual_address, uint16_t flags);

#endif