#include "PhysicalMemoryManager.h"

#include <Kernel/Core/Stivale.h>
#include <LibC/string.h>
#include <LibC/stdio.h>

#include "MemoryDefinitions.h"

uint64_t PhysicalMemoryManager::m_TotalMemory;
uint64_t PhysicalMemoryManager::m_Pages;
uint64_t PhysicalMemoryManager::m_BitmapSize;

Bitmap PhysicalMemoryManager::m_Bitmap(0, 0);

void PhysicalMemoryManager::Initialize(StivaleStruct* bootloaderData)
{
	StivaleMemoryMapEntry* memoryMap = (StivaleMemoryMapEntry*)bootloaderData->MemoryMapAddress;
	printf("[PMM] Memory Address: %X\n", bootloaderData->MemoryMapAddress);
	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		StivaleMemoryMapEntry& entry = memoryMap[i];
		printf("[PMM] [Entry %d] [%X - %X]: Size %X, Type %X\n", i, entry.Address, entry.Address + entry.Length, entry.Length, entry.Type);
		m_TotalMemory += entry.Length;
	}

	m_Pages = (uint64_t)m_TotalMemory / PAGESIZE;
	m_BitmapSize = (uint64_t)m_Pages / BYTESIZE;

	printf("[PMM] Total Memory: %X\n", m_TotalMemory);
	printf("[PMM] Planned Pages: %u\n", m_BitmapSize);

	uint64_t bitmapBase = 0;

	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		StivaleMemoryMapEntry& entry = memoryMap[i];
		if (entry.Type & StivaleMemoryType::USABLE && entry.Length >= m_BitmapSize)
		{
			m_Bitmap.SetData((uint8_t*)entry.Address + KERNEL_BASE_ADDRESS);
			m_Bitmap.SetSize(m_BitmapSize);
			bitmapBase = entry.Address;
			memset((uint64_t*)(uintptr_t)m_Bitmap.Data(), 0xFFFFFFFF, m_BitmapSize / BYTESIZE);
			break;
		}
	}

	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		StivaleMemoryMapEntry& entry = memoryMap[i];
		if (entry.Type & StivaleMemoryType::USABLE)
			FreeMemory(entry.Address, entry.Length);
	}

	ReserveMemory(bitmapBase, m_BitmapSize);
	ReserveMemory(0, 0x100000);

	printf("[PMM] Physical Memory Manager initialized!\n");
}

void PhysicalMemoryManager::FreeMemory(uint64_t baseAddress, uint64_t size)
{
	for (uint64_t i = baseAddress / PAGESIZE; i < ((baseAddress + size) / PAGESIZE + (size % PAGESIZE ? 1 : 0)); i++)
		m_Bitmap.SetBit(i, false);
}

void PhysicalMemoryManager::ReserveMemory(uint64_t baseAddress, uint64_t size)
{
	for (uint64_t i = baseAddress / PAGESIZE; i < ((baseAddress + size) / PAGESIZE + (size % PAGESIZE ? 1 : 0)); i++)
		m_Bitmap.SetBit(i, true);
}

void* PhysicalMemoryManager::AllocatePage()
{
	return AllocatePages(1);
}

void* PhysicalMemoryManager::AllocatePages(uint64_t pageCount)
{
	void* availablePage = GetAvailablePage();
	uint64_t baseAddress = (uint64_t)availablePage * PAGESIZE;
	uint64_t currentFree = 0;

	if (availablePage == nullptr)
	{
		printf("[PMM] Error: No free pages!\n");
		return nullptr;
	}

	for (uint64_t i = (uint64_t)availablePage; i < m_Bitmap.Size(); i++)
	{
		if (m_Bitmap.GetBit(i))
		{
			baseAddress += (currentFree + 1) * PAGESIZE;
			currentFree = 0;
			continue;
		}

		if (++currentFree == pageCount)
		{
			for (uint64_t j = 0; j < pageCount; j++)
				m_Bitmap.SetBit(j + baseAddress / PAGESIZE,true);
			return (void*) baseAddress;
		}
	}

	return nullptr;
}

void PhysicalMemoryManager::FreePage(uintptr_t address)
{
	FreePages(address, 1);
}

void PhysicalMemoryManager::FreePages(uintptr_t address, uint64_t pageCount)
{
	uint64_t startAddress = (uint64_t)address / PAGESIZE;
	for (uint64_t i = startAddress; i < startAddress + pageCount; i++)
		m_Bitmap.SetBit(i, false);
}

void* PhysicalMemoryManager::GetAvailablePage()
{
	return GetAvailablePageAfter(0);
}

void* PhysicalMemoryManager::GetAvailablePageAfter(uint64_t lowLimit)
{
	for (uint64_t i = lowLimit; i < m_Bitmap.Size(); i++)
		if (!m_Bitmap.GetBit(i))
			return (void*)i;
	return nullptr;
}