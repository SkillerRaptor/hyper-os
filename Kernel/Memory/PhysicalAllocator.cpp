#include "PhysicalAllocator.h"

#include <Kernel/Core/Stivale.h>
#include <LibC/string.h>
#include <LibC/stdio.h>

uint64_t PhysicalAllocator::m_TotalMemory;
uint64_t PhysicalAllocator::m_Pages;
uint64_t PhysicalAllocator::m_BitmapSize;

void PhysicalAllocator::Initialize(StivaleStruct* bootloaderData)
{
	StivaleMemoryMapEntry* memoryMap = (StivaleMemoryMapEntry*)bootloaderData->MemoryMapAddress;

	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		printf("[PMM] [Entry %d] [%X - %X]: Size %X, Type %X\n", i, memoryMap[i].Base, memoryMap[i].Base + memoryMap[i].Length, memoryMap[i].Length, memoryMap[i].Type);
		m_TotalMemory += memoryMap[i].Length;
	}

	m_Pages = (uint64_t) m_TotalMemory / PageSize;
	m_BitmapSize = (uint64_t) m_Pages / ByteSize;

	printf("[PMM] Total Memory: %X\n", m_TotalMemory);
	printf("[PMM] Total Memory: %u\n", m_TotalMemory);
	printf("[PMM] Pages: %u\n", m_Pages);
	printf("[PMM] Bitmap Size: %u\n", m_BitmapSize);
}

void* PhysicalAllocator::AllocatePage()
{
}

void PhysicalAllocator::FreePage(uint64_t page)
{
}

void* PhysicalAllocator::GetAvailablePages()
{
}
