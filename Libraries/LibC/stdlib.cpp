#include "stdlib.h"

#include <Kernel/Memory/MemoryDefinitions.h>
#include <Kernel/Memory/PhysicalMemoryManager.h>
#include <Kernel/Memory/VirtualMemoryManager.h>

#include "stdio.h"
#include "string.h"

struct HeapHeader
{
    uint64_t Size;
    uint64_t Pages;
};

void abort()
{
#if defined(__is_libk)
    // TODO: Add proper kernel panic.
    printf("Kernel: panic: abort()\n");
#else
    // TODO: Abnormally terminate the process as if by SIGABRT.
    printf("abort()\n");
#endif

    while (true);
}

void* malloc(size_t size)
{
    static uint64_t top = KERNEL_BASE_ADDRESS;

    size = (size + 7) / 8 * 8;
    uint64_t byteSize = size + sizeof(HeapHeader);
    uint64_t pageCount = (byteSize + 0xFFF) / 0x1000 + 1;
    uint64_t out = top;

    void* ptr = PhysicalMemoryManager::AllocatePages(pageCount);

    if (ptr == nullptr)
    {
        // TODO: Adding Panic for failed Memory Allocation
        return nullptr;
    }

    VirtualMemoryManager::PageTable* pageTable = VirtualMemoryManager::CreateNewPageTable();
    VirtualMemoryManager::MapPages(pageTable, KERNEL_BASE_ADDRESS, (uintptr_t) ptr, pageCount, (uintptr_t) VirtualMemoryManager::PageTableAttributes::READ_AND_WRITE);

    top += 0x1000 * (pageCount + 1);
    out += 0x1000 * pageCount - size;

    HeapHeader* heapHeader = (HeapHeader*)out;
    heapHeader->Size = size;
    heapHeader->Pages = pageCount;

    return (void*) out + sizeof(HeapHeader);
}

void* calloc(size_t num, size_t size)
{
    void* ptr = malloc(num * size);
	memset(ptr, 0, num * size);
	return ptr;
}

void* realloc(void* ptr, size_t size)
{
    void* newPtr = malloc(size);

    if (ptr != nullptr)
    {
        size_t ptrSize = (uint64_t) ptr - 16;
        memcpy(newPtr, ptr, ptrSize);
        free(ptr);
    }

    return newPtr;
}

void free(void* ptr)
{
    HeapHeader* heapHeader = (HeapHeader*)((uint64_t) ptr - 16);
    uint64_t start = (uint64_t)ptr & ~(0x1000 - 1);
    uint64_t pageCount = (heapHeader->Size + 0xFFF) / 0x1000 + 1;

    if (heapHeader->Pages != pageCount)
        return;

    uint64_t virtualAddress = (uint64_t)start + pageCount * 0x1000;

    VirtualMemoryManager::PageTable* pageTable = VirtualMemoryManager::GetPageTable(virtualAddress);
    uint64_t physicalAddress = VirtualMemoryManager::GetEntry(pageTable, virtualAddress);

    VirtualMemoryManager::UnmapPages(pageTable, virtualAddress, pageCount);
	PhysicalMemoryManager::FreePages(physicalAddress, pageCount);
}