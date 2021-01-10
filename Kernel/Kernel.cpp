#include <LibC/stdio.h>
#include <AK/IO.h>

#include "Core/GDT.h"
#include "Core/IDT.h"
#include "Core/PIC.h"
#include "Core/Stivale.h"
#include "Core/Terminal.h"
#include "Memory/PhysicalMemoryManager.h"
#include "Memory/VirtualMemoryManager.h"

__BEGIN_DECLS

void KernelEarlyMain(StivaleStruct* bootloaderData);

static uint8_t stack[4096] = { 0 };

__attribute__((section(".stivalehdr"), used))
struct StivaleHeader header = {
	.Stack = (uintptr_t)stack + sizeof(stack),
	.Flags = 0,
	.FramebufferWidth = 0,	
	.FramebufferHeight = 0,
	.FramebufferBpp = 0,
	.EntryPoint = (uintptr_t) KernelEarlyMain
};

void KernelMain()
{
	printf("[Kernel] HyperOS finished booting...\n");

	while (true)
		asm volatile ("hlt");
}

void KernelInit()
{
	KernelMain();
}

void KernelEarlyMain(StivaleStruct* bootloaderData)
{
	Terminal::Initialize();

	printf("[Kernel] HyperOS booting...\n");

	GDT::Get().CreateBasicDescriptor();
	GDT::Get().Install();

	PIC::Get().ReMap(0x20, 0x28);

	IDT::Get().CreateBasicTables();
	IDT::Get().Install();

	PhysicalMemoryManager::Get().Initialize(bootloaderData);
	
	VirtualMemoryManager::PageTable* pageTable = VirtualMemoryManager::Get().CreateNewPageTable();

	for (uint64_t i = 0; i < PhysicalMemoryManager::Get().GetTotalMemory() * 8; i += 0x1000)
	{
		VirtualMemoryManager::Get().MapPage(pageTable, (void*) i, (void*) i, 0);
	}
	
	asm("mov %0, %%cr3" :: "r" (pageTable) : "memory");

	KernelInit();
}
__END_DECLS