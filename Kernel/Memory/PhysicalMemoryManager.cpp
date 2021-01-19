#include "PhysicalMemoryManager.h"

#include <LibC/stdio.h>

size_t PhysicalMemoryManager::s_LastUsedIndex = 0;
uintptr_t PhysicalMemoryManager::s_HighestPage = 0;

Bitmap PhysicalMemoryManager::s_Bitmap;

void PhysicalMemoryManager::Initialize(Stivale2_MmapEntry* memoryMap, size_t memoryMapEntries)
{
	printf("[PMM] Memory Address: %X\n", (uint64_t)memoryMap);

	/* Calculate bitmap size */
	for (size_t i = 0; i < memoryMapEntries; i++)
	{
		Stivale2_MmapEntry& entry = memoryMap[i];
		printf("[PMM] [Entry %d] [%X - %X]: Size %X, Type %X\n", i, entry.Base, entry.Base + entry.Length, entry.Length, entry.Type);

		if (entry.Type != STIVALE2_MMAP_USABLE)
			continue;

		uintptr_t top = (uintptr_t)(entry.Base + entry.Length);

		if (top > s_HighestPage)
			s_HighestPage = top;
	}

	size_t memorySize = ((size_t)s_HighestPage + (PAGE_SIZE - 1)) / PAGE_SIZE;
	size_t bitmapSize = memorySize / 8;

	/* Find location for the bitmap*/
	for (size_t i = 0; i < memoryMapEntries; i++)
	{
		Stivale2_MmapEntry& entry = memoryMap[i];
		if (entry.Type != STIVALE2_MMAP_USABLE)
			continue;

		if (entry.Length >= bitmapSize) {
			s_Bitmap.SetData((uint8_t*)(entry.Base + KERNEL_BASE_ADDRESS));

			memset(s_Bitmap.GetData(), 0xFF, bitmapSize);

			entry.Base += bitmapSize;
			entry.Length -= bitmapSize;
			break;
		}
	}

	for (size_t i = 0; i < memoryMapEntries; i++)
	{
		Stivale2_MmapEntry& entry = memoryMap[i];
		if (entry.Type != STIVALE2_MMAP_USABLE)
			continue;

		for (uintptr_t j = 0; j < entry.Length; j += PAGE_SIZE)
			s_Bitmap.SetBit((entry.Base + j) / PAGE_SIZE, false);
	}

	printf("[PMM] Physical Memory Manager initialized!\n");
}

void* PhysicalMemoryManager::InnerAllocate(size_t pageCount, size_t limit)
{
	size_t p = 0;

	while (s_LastUsedIndex < limit)
	{
		if (s_Bitmap[s_LastUsedIndex++] == false)
		{
			if (p++ == pageCount)
			{
				size_t page = s_LastUsedIndex - pageCount;
				for (size_t i = page; i < s_LastUsedIndex; i++)
					s_Bitmap.SetBit(i, true);
				return (void*)(page * PAGE_SIZE);
			}
		}
		else
		{
			p = 0;
		}
	}

	return nullptr;
}

void* PhysicalMemoryManager::AllocatePage()
{
	return AllocatePages(1);
}

void* PhysicalMemoryManager::AllocatePages(size_t pageCount)
{
	size_t length = s_LastUsedIndex;
	void* address = InnerAllocate(pageCount, s_HighestPage / PAGE_SIZE);
	if (address == nullptr)
	{
		s_LastUsedIndex = 0;
		address = InnerAllocate(pageCount, length);
	}

	return address;
}

void* PhysicalMemoryManager::CallocatePage()
{
	return CallocatePages(1);
}

void* PhysicalMemoryManager::CallocatePages(size_t pageCount)
{
	char* address = (char*)AllocatePages(pageCount);

	if (address == nullptr)
		return nullptr;

	uint64_t* ptr = (uint64_t*)(address + KERNEL_BASE_ADDRESS);

	for (size_t i = 0; i < pageCount * (PAGE_SIZE / sizeof(uint64_t)); i++)
		ptr[i] = 0;

	return address;
}

void PhysicalMemoryManager::FreePage(void* address)
{
	FreePages(address, 1);
}

void PhysicalMemoryManager::FreePages(void* address, size_t pageCount)
{
	uint64_t startPage = (uint64_t)address / PAGE_SIZE;
	for (size_t i = startPage; i < startPage + pageCount; i++)
		s_Bitmap.SetBit(i, false);
}