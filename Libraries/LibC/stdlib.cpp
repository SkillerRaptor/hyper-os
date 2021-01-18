#include <LibC/stdlib.h>

#include <Kernel/Memory/PhysicalMemoryManager.h>

#include <LibC/stdio.h>
#include <LibC/string.h>

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
    return nullptr;
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

}