#include "VirtualMemoryManager.h"

#include <LibC/string.h>

#include "MemoryDefinitions.h"
#include "PhysicalMemoryManager.h"

#include <LibC/stdio.h>

VirtualMemoryManager::PageTable* VirtualMemoryManager::CreateNewPageTable()
{
	PageTable* newPML4 = (PageTable*)PhysicalMemoryManager::AllocatePage();

	if (newPML4 == nullptr)
	{
		// TODO: Panic for Address space allocation failed
		return nullptr;
	}

	memset((void*)(uintptr_t)newPML4 + KERNEL_BASE_ADDRESS, 0, 0x1000);

	return newPML4;
}

void VirtualMemoryManager::MapPage(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t physicalAddress, uintptr_t flags)
{
	MapPages(pageTable, virtualAddress, physicalAddress, 1, flags);
}

void VirtualMemoryManager::MapPages(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t physicalAddress, uintptr_t pageCount, uintptr_t flags)
{
	uint64_t higherFlags = (uint64_t)PageTableAttributes::READ_AND_WRITE | (uint64_t)PageTableAttributes::USER;

	while (pageCount--)
	{
		PageTableOffsets offset = SplitVirtualToOffsets(virtualAddress);
		PageTable* virtualPML4 = (PageTable*)((uint64_t)pageTable + KERNEL_BASE_ADDRESS);
		PageTable* virtualPDP = GetEntryOrAllocate(virtualPML4, offset.PML4, higherFlags);
		PageTable* virtualPD = GetEntryOrAllocate(virtualPDP, offset.PDP, higherFlags);
		PageTable* virtualPT = GetEntryOrAllocate(virtualPD, offset.PD, higherFlags);
		virtualPT->Entries[offset.PT] = physicalAddress | flags | (uint64_t)PageTableAttributes::PRESENT;
		virtualAddress = virtualAddress + 0x1000;
		physicalAddress = physicalAddress + 0x1000;
	}
}

bool VirtualMemoryManager::UnmapPage(PageTable* pageTable, uintptr_t virtualAddress)
{
	return UnmapPages(pageTable, virtualAddress, 1);
}

bool VirtualMemoryManager::UnmapPages(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t pageCount)
{
	while (pageCount--)
	{
		PageTableOffsets offset = SplitVirtualToOffsets(virtualAddress);
		PageTable* virtualPML4 = (PageTable*)((uintptr_t)pageTable + KERNEL_BASE_ADDRESS);
		PageTable* virtualPDP = GetEntryOrNull(virtualPML4, offset.PML4);

		if (!virtualPDP)
			return false;

		PageTable* virtualPD = GetEntryOrNull(virtualPDP, offset.PDP);

		if (!virtualPD)
			return false;

		PageTable* virtualPT = GetEntryOrNull(virtualPD, offset.PD);

		if (!virtualPT)
			return false;

		virtualPT->Entries[offset.PT] = 0;
		virtualAddress = virtualAddress + 0x1000;
	}

	return true;
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetPageTable(uintptr_t virtualAddress)
{
	PageTable* virtualPML4 = (PageTable*)(virtualAddress + KERNEL_BASE_ADDRESS);
	return virtualPML4;
}

uint64_t VirtualMemoryManager::GetEntry(PageTable* pageTable, uintptr_t virtualAddress)
{
	PageTableOffsets offset = SplitVirtualToOffsets(virtualAddress);
	PageTable* virtualPML4 = (PageTable*)((uintptr_t)pageTable + KERNEL_BASE_ADDRESS);
	PageTable* virtualPDP = GetEntryOrNull(virtualPML4, offset.PML4);

	if (!virtualPDP)
		return 0;

	PageTable* virtualPD = GetEntryOrNull(virtualPDP, offset.PDP);

	if (!virtualPD)
		return 0;

	PageTable* virtualPT = GetEntryOrNull(virtualPD, offset.PD);

	if (!virtualPT)
		return 0;

	return virtualPT->Entries[offset.PT];
}

VirtualMemoryManager::PageTableOffsets VirtualMemoryManager::SplitVirtualToOffsets(uintptr_t virtualAddress)
{
	PageTableOffsets offset;
	offset.PML4 = (virtualAddress >> 39) & 0x1FF;
	offset.PDP = (virtualAddress >> 30) & 0x1FF;
	offset.PD = (virtualAddress >> 21) & 0x1FF;
	offset.PT = (virtualAddress >> 12) & 0x1FF;
	return offset;
}

uintptr_t VirtualMemoryManager::JoinOffsetsToVirtual(PageTableOffsets offset)
{
	return (uintptr_t)((offset.PML4 << 39) | (offset.PDP << 30) | (offset.PD << 21) | (offset.PT << 12));
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetEntryOrNull(PageTable* table, size_t offset)
{
	uintptr_t entryAddress = table->Entries[offset];
	return !(entryAddress & (uint64_t)PageTableAttributes::PRESENT) ? nullptr : (PageTable*)((entryAddress + ~(0xFFF | (1ULL << 63))) + KERNEL_BASE_ADDRESS);
}

VirtualMemoryManager::PageTable* VirtualMemoryManager::GetEntryOrAllocate(PageTable* table, size_t offset, uint64_t flags)
{
	uint64_t entryAddress = table->Entries[offset];
	if (!(entryAddress & (uint64_t)PageTableAttributes::PRESENT))
	{
		table->Entries[offset] = (uint64_t)PhysicalMemoryManager::AllocatePage();
		entryAddress = table->Entries[offset];

		if (!entryAddress)
		{
			// TODO: Adding failed to allocate a page for a paging table
			return nullptr;
		}

		table->Entries[offset] |= flags | (uint64_t)PageTableAttributes::PRESENT;
		memset((void*)(entryAddress + KERNEL_BASE_ADDRESS), 0, 0x1000);
	}

	return (PageTable*)((entryAddress & ~(0xFFF | (1ULL << 63))) + KERNEL_BASE_ADDRESS);
}
