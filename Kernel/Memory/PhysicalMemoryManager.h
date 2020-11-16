#pragma once

#include <AK/Bitmap.h>
#include <AK/NonCopyable.h>
#include <AK/NonMoveable.h>
#include <LibC/stdint.h>

struct StivaleStruct;

class PhysicalMemoryManager : public NonCopyable, NonMoveable
{
private:
	static uint64_t m_TotalMemory;
	static uint64_t m_Pages;
	static uint64_t m_BitmapSize;
	static Bitmap m_Bitmap;

public:
	static void Initialize(StivaleStruct* bootloaderData);

	static void FreeMemory(uint64_t baseAddress, uint64_t size);
	static void ReserveMemory(uint64_t baseAddress, uint64_t size);

	static void* AllocatePage();
	static void* AllocatePages(uint64_t pageCount);
	static void FreePage(void* address);
	static void FreePages(void* address, uint64_t pageCount);
	static void* GetAvailablePage();
	static void* GetAvailablePageAfter(uint64_t lowLimit);
};