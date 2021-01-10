#pragma once

#include <Ak/Bitmap.h>
#include <AK/NonCopyable.h>
#include <AK/NonMoveable.h>
#include <Kernel/Core/Stivale.h>

class PhysicalMemoryManager : public NonCopyable, NonMoveable
{
private:
	static constexpr uint64_t KERNEL_BASE_ADDRESS = 0xFFFF800000000000;
	static constexpr uint64_t PAGE_SIZE = 0x1000;

	uint64_t m_TotalMemory;
	uint64_t m_Pages;

	Bitmap m_Bitmap;

	static PhysicalMemoryManager m_Instance;

public:
	PhysicalMemoryManager() = default;

	void Initialize(StivaleStruct* bootloaderData);

	void ReserveMemory(void* baseAddress, size_t size);
	void FreeMemory(void* baseAddress, size_t size);

	void* AllocatePage();
	void* AllocatePages(size_t pageCount);

	void FreePage(void* address);
	void FreePages(void* address, size_t pageCount);

	uint64_t GetTotalMemory() const;

	static PhysicalMemoryManager& Get();

private:
	void* GetAvailablePage();
	void* GetAvailablePageAfter(uint64_t lowLimit);
};