#include <Kernel/Memory/VirtualMemoryManager.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Kernel/Memory/PhysicalMemoryManager.h>

VirtualMemoryManager::Pagemap* VirtualMemoryManager::s_KernelPagemap;

void VirtualMemoryManager::Initialize(Stivale2_MmapEntry* memoryMap, size_t memoryMapEntries)
{
	s_KernelPagemap = CreateNewPagemap();

	for (uintptr_t ptr = 0; ptr < 0x100000000; ptr += PhysicalMemoryManager::PAGE_SIZE)
		MapPage(s_KernelPagemap, (void*)ptr, (void*)(PhysicalMemoryManager::PHYSICAL_MEMORY_OFFSET + (uint64_t)ptr), PagemapAttributes::PRESENT | PagemapAttributes::READ_AND_WRITE);

	for (uintptr_t ptr = 0; ptr < 0x80000000; ptr += PhysicalMemoryManager::PAGE_SIZE)
		MapPage(s_KernelPagemap, (void*)ptr, (void*)(PhysicalMemoryManager::KERNEL_BASE_ADDRESS + (uint64_t)ptr), PagemapAttributes::PRESENT | PagemapAttributes::READ_AND_WRITE);

	for (size_t i = 0; i < memoryMapEntries; i++)
	{
		Stivale2_MmapEntry& entry = memoryMap[i];
		for (uintptr_t ptr = 0; ptr < entry.Length; ptr += PhysicalMemoryManager::PAGE_SIZE)
			MapPage(s_KernelPagemap, (void*)ptr, (void*)(PhysicalMemoryManager::PHYSICAL_MEMORY_OFFSET + (uint64_t)ptr), PagemapAttributes::PRESENT | PagemapAttributes::READ_AND_WRITE);
	}

	printf("[VMM] Virtual Memory Manager initialized!\n");

	SwitchPagemap(s_KernelPagemap);
}

VirtualMemoryManager::Pagemap* VirtualMemoryManager::CreateNewPagemap()
{
	Pagemap* pagemap = (Pagemap*)malloc(sizeof(Pagemap));
	pagemap->TopLevel = (uintptr_t*)PhysicalMemoryManager::AllocatePage();
	return pagemap;
}

void VirtualMemoryManager::SwitchPagemap(Pagemap* pagemap)
{
	asm("mov %0, %%cr3" :: "r" (pagemap->TopLevel) : "memory");
}

void VirtualMemoryManager::MapPage(Pagemap* pageMap, void* physicalAddress, void* virtualAddress, uint16_t flags)
{
	uintptr_t pml4Entry = ((uintptr_t)virtualAddress & ((uintptr_t)0x1ff << 39)) >> 39;
	uintptr_t pml3Entry = ((uintptr_t)virtualAddress & ((uintptr_t)0x1ff << 30)) >> 30;
	uintptr_t pml2Entry = ((uintptr_t)virtualAddress & ((uintptr_t)0x1ff << 21)) >> 21;
	uintptr_t pml1Entry = ((uintptr_t)virtualAddress & ((uintptr_t)0x1ff << 12)) >> 12;

	uintptr_t* pml4 = pageMap->TopLevel;

	uintptr_t* pml3 = GetNextLevel(pml4, pml4Entry);
	if (pml3 == nullptr)
		return;

	uintptr_t* pml2 = GetNextLevel(pml3, pml3Entry);
	if (pml2 == nullptr)
		return;

	uintptr_t* pml1 = GetNextLevel(pml2, pml2Entry);
	if (pml1 == nullptr)
		return;

	pml1[pml1Entry] = (uintptr_t)((uint64_t)physicalAddress | flags);
}

uintptr_t* VirtualMemoryManager::GetNextLevel(uintptr_t* currentLevel, size_t entry)
{
	uintptr_t level;

	if (currentLevel[entry] & PagemapAttributes::PRESENT)
	{
		level = currentLevel[entry] & ~((uintptr_t)0xfff);
	}
	else
	{
		level = (uintptr_t)PhysicalMemoryManager::CallocatePage();
		if (level == 0)
			return nullptr;
		currentLevel[entry] = level | PagemapAttributes::PRESENT | PagemapAttributes::READ_AND_WRITE | PagemapAttributes::USER_SUPERVISOR;
	}

	return (uintptr_t*)level;
}
