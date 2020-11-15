#include <AK/IO.h>
#include <LibC/stdio.h>

#include "Core/GDT.h"
#include "Core/IDT.h"
#include "Core/PIC.h"
#include "Core/Stivale.h"
#include "Core/Terminal.h"

__BEGIN_DECLS

void KernelEarlyMain(StivaleStruct* bootloaderData);

static char stack[4096] = { 0 };

__attribute__((section(".stivalehdr"), used))
struct StivaleHeader header = {
	.Stack = (uint64_t)(uintptr_t)stack + sizeof(stack),
	.Flags = 0,
	.FramebufferWidth = 0,
	.FramebufferHeight = 0,
	.FramebufferBpp = 0,
	.EntryPoint = (uint64_t)(uintptr_t)KernelEarlyMain
};

void KernelMain()
{
	printf("Hello, Kernel World!\n");

	/*
	char oldKey = 0;
	char currentKey = 0;
	for (;;)
	{
		oldKey = currentKey;
		currentKey = IO::In8(0x60);
		if (oldKey != currentKey)
			printf("ScanCode: %c\n", currentKey);
	}
	*/

	asm volatile ("hlt");
}

void KernelInit()
{
	KernelMain();
}

void KernelEarlyMain(StivaleStruct* bootloaderData)
{
	Terminal::Initialize();

	GDT::Get().CreateBasicDescriptor();
	GDT::Get().Install();

	PIC::Get().ReMap(0x20, 0x28);

	IDT::Get().CreateBasicTables();
	IDT::Get().Install();

	KernelInit();
}
__END_DECLS