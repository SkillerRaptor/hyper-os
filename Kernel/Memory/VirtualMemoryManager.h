#pragma once

#include <LibC/stddef.h>

class VirtualMemoryManager
{
public:
	static constexpr uint64_t KERNEL_BASE_ADDRESS = 0xFFFF800000000000;
	static constexpr size_t PAGE_SIZE = 4096;
	static constexpr size_t EntryCount = 512;

	enum PageAttributes : uint16_t
	{
		PRESENT = 1 << 0,
		READ_AND_WRITE = 1 << 1,
		USER_SUPERVISOR = 1 << 2,
		WRITE_TROUGH = 1 << 3,
		CACHE_DISABLED = 1 << 4,
		ACCESSED = 1 << 5,
		SIZE_4KB = 1 << 7
	};

	struct PACKED PageDirectoryEntry
	{
		PageAttributes Attributes : 9;
		uint8_t Available : 4;
		uint64_t Address : 52;
	};

	struct PACKED PageTable
	{
		PageDirectoryEntry Entries[EntryCount];
	};

	struct PageTableOffsets
	{
		uint64_t PML4;
		uint64_t PDP;
		uint64_t PD;
		uint64_t PT;
	};

	static VirtualMemoryManager m_Instance;

public:
	PageTable* CreateNewPageTable();

	void MapPage(PageTable* pageTable, void* virtualAddress, void* physicalAddress, uint16_t flags);
	void MapPages(PageTable* pageTable, void* virtualAddress, void* physicalAddress, uint16_t flags, size_t pageCount);
	bool UnmapPage(PageTable* pageTable, void* virtualAddress);
	bool UnmapPages(PageTable* pageTable, void* virtualAddress, size_t pageCount);

	PageTable* GetPageTable(uintptr_t virtualAddress);
	uint64_t GetEntry(PageTable* pageTable, uint64_t virtualAddress);

	static VirtualMemoryManager& Get();

private:
	PageTableOffsets SplitVirtualToOffsets(uint64_t virtualAddress);
	uint64_t JoinOffsetsToVirtual(PageTableOffsets offset);

	PageTable* GetEntryOrNull(PageTable* table, size_t offset);
	PageTable* GetEntryOrAllocate(PageTable* table, size_t offset, uint16_t flags);

	friend PageAttributes operator|(PageAttributes left, PageAttributes right)
	{
		return static_cast<PageAttributes>(static_cast<uint16_t>(left) | static_cast<uint16_t>(right));
	}
};