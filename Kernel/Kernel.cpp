#include <AK/IO.h>
#include <LibC/stdio.h>
#include <Kernel/Core/GDT.h>
#include <Kernel/Core/IDT.h>
#include <Kernel/Core/IRQManager.h>
#include <Kernel/Core/PIC.h>
#include <Kernel/Core/Terminal.h>
#include <Kernel/Stivale/Stivale2.h>
#include <Kernel/Memory/PhysicalMemoryManager.h>
#include <Kernel/Memory/VirtualMemoryManager.h>
#include <LibGUI/Painter.h>
#include <LibGUI/Window.h>
#include <LibGUI/WindowManager.h>

__BEGIN_DECLS

void KernelMain(Stivale2_Struct* bootloaderData)
{
	bootloaderData = (Stivale2_Struct*)((void*)((uint64_t)bootloaderData + PhysicalMemoryManager::KERNEL_BASE_ADDRESS));

	Terminal::Initialize();

	printf("[Kernel] HyperOS booting...\n");

	GDT::Get().CreateBasicDescriptor();
	GDT::Get().Install();

	IRQManager::Install();
	IDT::Get().Install();

	PIC::Get().ReMap(0x20, 0x28);

	Stivale2_StructTagMemmap* memmapTag = (Stivale2_StructTagMemmap*)Stivale2_GetTag(bootloaderData, STIVALE2_STRUCT_TAG_MEMMAP_ID);

	PhysicalMemoryManager::Initialize(memmapTag->Memmap, memmapTag->Entries);
	VirtualMemoryManager::Initialize(memmapTag->Memmap, memmapTag->Entries);

	GDT::Get().Install();
	IDT::Get().Install();

	printf("[Kernel] HyperOS finished booting...\n");

	Stivale2_StructTagFramebuffer* framebufferTag = (Stivale2_StructTagFramebuffer*)Stivale2_GetTag(bootloaderData, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

	FrameBufferInfo frameBufferInfo{};
	frameBufferInfo.FramebufferAddress = framebufferTag->FramebufferAddress + PhysicalMemoryManager::PHYSICAL_MEMORY_OFFSET;
	frameBufferInfo.FramebufferPitch = framebufferTag->FramebufferPitch;
	frameBufferInfo.FramebufferWidth = framebufferTag->FramebufferWidth;
	frameBufferInfo.FramebufferHeight = framebufferTag->FramebufferHeight;
	frameBufferInfo.FramebufferBpp = framebufferTag->FramebufferBpp;

	Painter& painter = Painter::Get();
	painter.Init(frameBufferInfo);
	painter.Clear(Color{ 50, 50, 50 });

	Window window1{};
	window1.SetTitle("Hello, how are you today? Just tell me :^)");
	window1.SetRect(Rect{ 50, 50, 500, 300 });

	Window window2{};
	window2.SetTitle("I'm good :) How are you?");
	window2.SetRect(Rect{ 350, 400, 500, 300 });

	WindowManager windowManager = WindowManager();
	windowManager.PaintWindowFrame(window1);
	windowManager.PaintWindowFrame(window2);

	asm volatile ("sti" :: : "memory");
	while (true)
	{
		asm volatile ("hlt" :: : "memory");
	}
}
__END_DECLS
