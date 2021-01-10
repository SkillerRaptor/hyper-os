#include "PhysicalMemoryManager.h"

#include <LibC/stdio.h>

PhysicalMemoryManager PhysicalMemoryManager::m_Instance;

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

	m_Pages = static_cast<uint64_t>((m_TotalMemory / 4096) / 8);

	printf("[PMM] Total Memory: %X\n", m_TotalMemory);

	uint64_t bitmapBase = 0;

	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		StivaleMemoryMapEntry& entry = memoryMap[i];
		if (entry.Type & StivaleMemoryType::USABLE && entry.Length >= m_Pages)
		{
			m_Bitmap.SetData((uint8_t*)(entry.Address + KERNEL_BASE_ADDRESS));
			m_Bitmap.SetSize(m_Pages);
			bitmapBase = entry.Address;
			memset((uint64_t*)m_Bitmap.GetData(), 0xFFFFFFFF, m_Pages / 8);
			break;
		}
	}

	for (uint64_t i = 0; i < bootloaderData->MemoryMapEntries; i++)
	{
		StivaleMemoryMapEntry& entry = memoryMap[i];
		if (entry.Type & StivaleMemoryType::USABLE)
		{
			FreeMemory((void*)entry.Address, entry.Length);
		}
	}

	ReserveMemory((void*)bitmapBase, m_Pages);
	ReserveMemory((void*)0, 0x100000);

	printf("[PMM] Physical Memory Manager initialized!\n");
}

void* PhysicalMemoryManager::AllocatePage()
{
	return AllocatePages(1);
}

void* PhysicalMemoryManager::AllocatePages(size_t pageCount)
{
	void* firstPage = GetAvailablePage();
	void* baseAddress = (void*)((uint64_t)firstPage * PAGE_SIZE);
	uint64_t currentFree = 0;

	if (firstPage == nullptr)
	{
		printf("[PMM] Error: No free pages!\n");
		return nullptr; // TODO: Page Frame Swap to file!
	}

	for (size_t i = (uint64_t)firstPage; i < m_Bitmap.GetSize(); i++)
	{
		if (m_Bitmap[i] == true)
		{
			baseAddress = (void*)((uint64_t)baseAddress + ((currentFree + 1) * PAGE_SIZE));
			currentFree = 0;
			continue;
		}

		if (++currentFree == pageCount)
		{
			for (size_t j = 0; j < pageCount; j++)
			{
				m_Bitmap.SetBit((uint64_t)baseAddress / PAGE_SIZE + j, true);
			}
			return baseAddress;
		}
	}

	return nullptr;
}

void PhysicalMemoryManager::FreePage(void* address)
{
	FreePages(address, 1);
}

void PhysicalMemoryManager::FreePages(void* address, size_t pageCount)
{
	uint64_t startPage = (uint64_t)address / PAGE_SIZE;
	for (size_t i = startPage; i < startPage + pageCount; i++)
	{
		m_Bitmap.SetBit(i, false);
	}
}

void PhysicalMemoryManager::ReserveMemory(void* baseAddress, size_t size)
{
	uint64_t offsetAddress = ((uint64_t)baseAddress + size) / PAGE_SIZE;
	for (size_t i = (uint64_t)baseAddress / PAGE_SIZE; i < (offsetAddress + (size % PAGE_SIZE ? 1 : 0)); i++)
	{
		m_Bitmap.SetBit(i, true);
	}
}

void PhysicalMemoryManager::FreeMemory(void* baseAddress, size_t size)
{
	uint64_t offsetAddress = ((uint64_t)baseAddress + size) / PAGE_SIZE;
	for (size_t i = (uint64_t)baseAddress / PAGE_SIZE; i < (offsetAddress + (size % PAGE_SIZE ? 1 : 0)); i++)
	{
		m_Bitmap.SetBit(i, false);
	}
}

void* PhysicalMemoryManager::GetAvailablePage()
{
	for (uint64_t i = 0; i < m_Bitmap.GetSize(); i++)
	{
		if (m_Bitmap[i] == false)
			return (void*)i;
	}

	return nullptr;
}

void* PhysicalMemoryManager::GetAvailablePageAfter(uint64_t lowLimit)
{
	for (uint64_t i = lowLimit; i < m_Bitmap.GetSize(); i++)
	{
		if (m_Bitmap[i] == false)
			return (void*)i;
	}

	return nullptr;
}

uint64_t PhysicalMemoryManager::GetTotalMemory() const
{
	return m_TotalMemory;
}

PhysicalMemoryManager& PhysicalMemoryManager::Get()
{
	return m_Instance;
}