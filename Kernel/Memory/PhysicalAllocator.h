#pragma once

#include <AK/NonCopyable.h>
#include <AK/NonMoveable.h>
#include <LibC/stdint.h>

struct StivaleStruct;

class PhysicalAllocator : public NonCopyable, NonMoveable
{
private:
	static constexpr uint16_t PageSize = 4096;
	static constexpr uint16_t ByteSize = 8;
	static uint64_t m_TotalMemory;
	static uint64_t m_Pages;
	static uint64_t m_BitmapSize;

public:
	static void Initialize(StivaleStruct* bootloaderData);

	static void* AllocatePage();
	static void FreePage(uint64_t page);
	static void* GetAvailablePages();
};