#pragma once

#include <Ak/Bitmap.h>
#include <AK/NonCopyable.h>
#include <AK/NonMoveable.h>
#include <Kernel/Core/Stivale.h>

class PhysicalMemoryManager : public NonCopyable, public NonMoveable
{
public:
	static constexpr uint64_t KERNEL_TOP_ADDRESS = 0xFFFFFFFF80000000;
	static constexpr uint64_t KERNEL_BASE_ADDRESS = 0xFFFF800000000000;
	static constexpr size_t PAGE_SIZE = 4096;

private:
	static size_t s_LastUsedIndex;
	static uintptr_t s_HighestPage;

	static Bitmap s_Bitmap;

public:
	static void Initialize(StivaleMemoryMapEntry* memoryMap, size_t memoryMapEntries);

	static void* AllocatePage();
	static void* AllocatePages(size_t pageCount);

	static void* CallocatePage();
	static void* CallocatePages(size_t pageCount);

	static void FreePage(void* address);
	static void FreePages(void* address, size_t pageCount);

private:
	static void* InnerAllocate(size_t pageCount, size_t limit);
};