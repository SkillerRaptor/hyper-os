#include <Kernel/Memory/pmm.h>

#include <string.h>
#include <AK/bitmap.h>
#include <AK/logger.h>
#include <Kernel/Memory/mm.h>

size_t last_used_index = 0;
uintptr_t highest_page = 0;

bitmap_t bitmap;

static void* pmm_inner_allocate(size_t page_count, size_t limit)
{
    size_t p = 0;

    while (last_used_index < limit)
    {
        if (bitmap_get_bit(bitmap, last_used_index++) == false)
        {
            if (p++ == page_count)
            {
                size_t page = last_used_index - page_count;
                for (size_t i = page; i < last_used_index; i++)
                    bitmap_set_bit(&bitmap, i, true);
                return (void*)(page * PAGE_SIZE);
            }
        }
        else
        {
            p = 0;
        }
    }

    return NULL;
}

void pmm_init(struct stivale2_mmap_entry* memory_map, size_t memory_map_entries)
{
    info("PMM: Initializing physical memory manager...");

    for (size_t i = 0; i < memory_map_entries; ++i)
    {
        struct stivale2_mmap_entry* entry = &memory_map[i];

        info("PMM: [Entry %d] [%X - %X]: Size %X, Type %X", i, entry->base, entry->base + entry->length, entry->length, entry->type);
        
        if (entry->type != STIVALE2_MMAP_USABLE)
            continue;

        uintptr_t top_address = (uintptr_t)(entry->base + entry->length);
        if (top_address > highest_page)
            highest_page = top_address;
    }

    size_t memory_size = ((size_t)highest_page + (PAGE_SIZE - 1)) / PAGE_SIZE;
    size_t bitmap_size = memory_size / BYTE_SIZE;

    for (size_t i = 0; i < memory_map_entries; ++i)
    {
        struct stivale2_mmap_entry* entry = &memory_map[i];

        if (entry->type != STIVALE2_MMAP_USABLE)
            continue;

        if (entry->length >= bitmap_size)
        {
            bitmap.data = (uint8_t*)(entry->base + PHYSICAL_MEMORY_OFFSET);

            memset(bitmap.data, 0xFF, bitmap_size);

            entry->base += bitmap_size;
            entry->length -= bitmap_size;
            break;
        }
    }

    for (size_t i = 0; i < memory_map_entries; ++i)
    {
        struct stivale2_mmap_entry* entry = &memory_map[i];

        if (entry->type != STIVALE2_MMAP_USABLE)
            continue;

        for (uintptr_t j = 0; j < entry->length; j += PAGE_SIZE)
            bitmap_set_bit(&bitmap, (entry->base + j) / PAGE_SIZE, false);
    }

    info("PMM: Physical memory manager initialized...");
}

void* pmm_allocate_pages(size_t page_count)
{
    size_t length = last_used_index;
    void* address = pmm_inner_allocate(page_count, highest_page / PAGE_SIZE);
    if(address == NULL)
    {
        last_used_index = 0;
        address = pmm_inner_allocate(page_count, length);
    }
    return address;
}

void* pmm_callocate_pages(size_t page_count)
{
    uint8_t* address = (uint8_t*)pmm_allocate_pages(page_count);

    if (address == NULL)
        return NULL;

    uint64_t* pointer = (uint64_t*)(address + PHYSICAL_MEMORY_OFFSET);

    for (size_t i = 0; i < page_count * (PAGE_SIZE / sizeof(uint64_t)); ++i)
        pointer[i] = 0x0;

    return address;
}

void pmm_free_pages(void* address, size_t page_count)
{
    uint64_t start_page = (uint64_t)address / PAGE_SIZE;
    for (size_t i = start_page; i < start_page + page_count; ++i)
        bitmap_set_bit(&bitmap, i, false);
}