#pragma once

#include <LibC/stdint.h>
#include <LibC/stddef.h>

class VirtualMemoryManager
{
public:
	enum PageTableAttributes : uint64_t
	{
		PRESENT = 1ULL << 0,
		READ_AND_WRITE = 1ULL << 1,
		USER = 1ULL << 2,
		PAT0 = 1ULL << 3,
		PAT1 = 1ULL << 4,
		PAT2 = 1ULL << 7,
		DIRTY = 1ULL << 5,
		SIZE_4KB = 1ULL << 7,
		NX = 1ULL << 63
	};

	friend PageTableAttributes operator|(PageTableAttributes left, PageTableAttributes right)
	{
		return static_cast<PageTableAttributes>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
	}

	struct PageTable
	{
		uintptr_t Entries[512];
	};

	struct PageTableOffsets
	{
		size_t PML4;
		size_t PDP;
		size_t PD;
		size_t PT;
	};

public:
	static PageTable* CreateNewPageTable();

	static void MapPage(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t physicalAddress, uintptr_t flags);
	static void MapPages(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t physicalAddress, uintptr_t pageCount, uintptr_t flags);
	static bool UnmapPage(PageTable* pageTable, uintptr_t virtualAddress);
	static bool UnmapPages(PageTable* pageTable, uintptr_t virtualAddress, uintptr_t pageCount);

	static PageTable* GetPageTable(uintptr_t virtualAddress);
	static uint64_t GetEntry(PageTable* pageTable, uintptr_t virtualAddress);

private:
	static PageTableOffsets SplitVirtualToOffsets(uintptr_t virtualAddress);
	static uintptr_t JoinOffsetsToVirtual(PageTableOffsets offset);

	static PageTable* GetEntryOrNull(PageTable* table, size_t offset);
	static PageTable* GetEntryOrAllocate(PageTable* table, size_t offset, uint64_t flags);
};