#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <Kernel/Memory/PhysicalMemoryManager.h>

struct HeapHeader
{
    uint64_t Pages;
    uint64_t Size;
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
    size_t pageCount = (size + (PhysicalMemoryManager::PAGE_SIZE - 1)) / PhysicalMemoryManager::PAGE_SIZE;

    void* ptr = (char*)PhysicalMemoryManager::CallocatePages(pageCount + 1);

    if (!ptr)
        return nullptr;

    ptr = (void*)((uint64_t)ptr + PhysicalMemoryManager::KERNEL_BASE_ADDRESS);

    HeapHeader* metadata = (HeapHeader*)ptr;
    ptr = (void*)((uint64_t)ptr + PhysicalMemoryManager::PAGE_SIZE);

    metadata->Pages = pageCount;
    metadata->Size = size;

    return ptr;
}

void* calloc(size_t num, size_t size)
{
    void* ptr = malloc(num * size);
    memset(ptr, 0, num * size);
    return ptr;
}

void* realloc(void* ptr, size_t size)
{
    if (!ptr)
        return malloc(size);

    HeapHeader* metadata = (HeapHeader*)((uint64_t)ptr - PhysicalMemoryManager::PAGE_SIZE);

    size_t currentSize = (metadata->Size + (PhysicalMemoryManager::PAGE_SIZE - 1)) / PhysicalMemoryManager::PAGE_SIZE;
    size_t newSize = (size + (PhysicalMemoryManager::PAGE_SIZE - 1)) / PhysicalMemoryManager::PAGE_SIZE;
    if (currentSize == newSize)
    {
        metadata->Size = newSize;
        return ptr;
    }

    void* newPtr = malloc(newSize);
    if (newPtr == nullptr)
        return nullptr;

    if (metadata->Size > newSize)
    {
        memcpy(newPtr, ptr, newSize);
    }
    else
    {
        memcpy(newPtr, ptr, metadata->Size);
    }

    free(ptr);

    return newPtr;
}

void free(void* ptr)
{
    HeapHeader* metadata = (HeapHeader*)((uint64_t)ptr - PhysicalMemoryManager::PAGE_SIZE);
    PhysicalMemoryManager::FreePages((void*)((uint64_t)metadata - PhysicalMemoryManager::KERNEL_BASE_ADDRESS), metadata->Pages + 1);
}

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void* operator new(size_t, void* ptr)
{
    return ptr;
}

void* operator new[](size_t, void* ptr)
{
    return ptr;
}

void operator delete(void* ptr)
{
    free(ptr);
}

void operator delete[](void* ptr)
{
    free(ptr);
}

void operator delete(void* ptr, size_t)
{
    free(ptr);
}

void operator delete[](void* ptr, size_t)
{
    free(ptr);
}