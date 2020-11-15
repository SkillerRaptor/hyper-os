#include <LibC/stdio.h>

#include "Core/GDT.h"
#include "Core/IDT.h"
#include "Core/PIC.h"
#include "Core/Stivale.h"
#include "Core/Terminal.h"
#include "Memory/PhysicalAllocator.h"

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

	//GDT::Get().CreateBasicDescriptor();
	//GDT::Get().Install();
	//
	//PIC::Get().ReMap(0x20, 0x28);
	//
	//IDT::Get().CreateBasicTables();
	//IDT::Get().Install();

	PhysicalAllocator::Initialize(bootloaderData);

	KernelInit();
}
__END_DECLS