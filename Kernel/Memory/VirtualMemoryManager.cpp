#include "VirtualMemoryManager.h"

#include <LibC/string.h>
#include <LibC/stdio.h>

#include "PhysicalMemoryManager.h"

VirtualMemoryManager VirtualMemoryManager::m_Instance;

VirtualMemoryManager::PageTable* VirtualMemoryManager::CreateNewPageTable()
{
	PageTable* pml4 = (PageTable*)PhysicalMemoryManager::Get().AllocatePage();

	if (pml4 == nullptr)
		return nullptr; // TODO: Panic for Address space allocation failed

	memset((void*)pml4, 0, 0x1000);

	return pml4;
}

void VirtualMemoryManager::MapPage(PageTable* pageTable, void* virtualAddress, void* physicalAddress, uint16_t flags)
{
	MapPages(pageTable, virtualAddress, physicalAddress, flags, 1);
}

void VirtualMemoryManager::MapPages(PageTable* pageTable, void* virtualAddress, void* physicalAddress, uint16_t flags, size_t pageCount)
{
	uint16_t higherFlags = PageAttributes::READ_AND_WRITE | PageAttributes::USER_SUPERVISOR;

	for (size_t i = 0; i < pageCount; i++)
	{
		PageTableOffsets offset = SplitVirtualToOffsets((uint64_t)virtualAddress);
		PageTable* virtualPML4 = (PageTable*)pageTable;
		PageTable* virtualPDP = GetEntryOrAllocate(virtualPML4, offset.PML4, higherFlags);
		PageTable* virtualPD = GetEntryOrAllocate(virtualPDP, offset.PDP, higherFlags);
		PageTable* virtualPT = GetEntryOrAllocate(virtualPD, offset.PD, higherFlags);

		PageDirectoryEntry entry{};
		entry.Address = (uint64_t)physicalAddress;
		entry.Attributes = entry.Attributes | (PageAttributes)flags | PageAttributes::PRESENT;
		virtualPT->Entries[offset.PT] = entry;
		virtualAddress = (void*)((uint64_t)virtualAddress + 0x1000);
		physicalAddress = (void*)((uint64_t)physicalAddress + 0x1000);
	}
}

bool VirtualMemoryManager::UnmapPage(PageTable* pageTable, void* virtualAddress)
{
	return false;
}

bool VirtualMemoryManager::UnmapPages(PageTable* pageTable, void* virtualAddress, size_t pageCount)
{
	return false;
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetPageTable(uintptr_t virtualAddress)
{
	return nullptr;
}

uint64_t VirtualMemoryManager::GetEntry(PageTable* pageTable, uint64_t virtualAddress)
{
	return 0;
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetEntryOrNull(PageTable* table, size_t offset)
{
	return nullptr;
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetEntryOrAllocate(PageTable* table, size_t offset, uint16_t flags)
{
	PageDirectoryEntry entryAddress = table->Entries[offset];

	if (!(entryAddress.Attributes & PageAttributes::PRESENT))
	{
		PageDirectoryEntry* entry = (PageDirectoryEntry*)PhysicalMemoryManager::Get().AllocatePage();
		table->Entries[offset] = *entry;
		entryAddress = table->Entries[offset];

		if (!entry)
			return nullptr; // TODO: Adding failed to allocate a page for a paging table

		table->Entries[offset].Attributes = table->Entries[offset].Attributes | (PageAttributes)flags | PageAttributes::PRESENT;
		memset((void*)entryAddress.Address, 0, 0x1000);
	}

	return (PageTable*)entryAddress.Address;
}

VirtualMemoryManager::PageTableOffsets VirtualMemoryManager::SplitVirtualToOffsets(uint64_t virtualAddress)
{
	PageTableOffsets offsets{};
	offsets.PML4 = (virtualAddress >> 39) & 0x1FF;
	offsets.PDP = (virtualAddress >> 30) & 0x1FF;
	offsets.PD = (virtualAddress >> 21) & 0x1FF;
	offsets.PT = (virtualAddress >> 12) & 0x1FF;
	return offsets;
}

uint64_t VirtualMemoryManager::JoinOffsetsToVirtual(PageTableOffsets offset)
{
	return (uint64_t)((offset.PML4 << 39) | (offset.PDP << 30) | (offset.PD << 21) | (offset.PT << 12));
}

VirtualMemoryManager& VirtualMemoryManager::Get()
{
	return m_Instance;
}