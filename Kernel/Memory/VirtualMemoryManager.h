#pragma once

#include <AK/NonCopyable.h>
#include <AK/NonMoveable.h>
#include <Kernel/Core/Stivale.h>
#include <LibC/stddef.h>

class VirtualMemoryManager : public NonCopyable, public NonMoveable
{
public:
	struct Pagemap
	{
		uintptr_t* TopLevel;
	};

private:
	enum PagemapAttributes : uint16_t
	{
		PRESENT = 1 << 0,
		READ_AND_WRITE = 1 << 1,
		USER_SUPERVISOR = 1 << 2,
		WRITE_TROUGH = 1 << 3,
		CACHE_DISABLED = 1 << 4,
		ACCESSED = 1 << 5,
		SIZE_4KB = 1 << 7
	};

	static Pagemap* s_KernelPagemap;

public:
	static void Initialize(StivaleMemoryMapEntry* memoryMap, size_t memoryMapEntries);

	static Pagemap* CreateNewPagemap();
	static void SwitchPagemap(Pagemap* pagemap);

	static void MapPage(Pagemap* pageMap, void* physicalAddress, void* virtualAddress, uint16_t flags);

private:
	static uintptr_t* GetNextLevel(uintptr_t* currentLevel, size_t entry);

	friend PagemapAttributes operator|(PagemapAttributes left, PagemapAttributes right)
	{
		return static_cast<PagemapAttributes>(static_cast<uint16_t>(left) | static_cast<uint16_t>(right));
	}
};