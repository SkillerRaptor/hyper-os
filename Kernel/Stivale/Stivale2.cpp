#include <Kernel/Stivale/Stivale2.h>

#include <Kernel/Memory/PhysicalMemoryManager.h>

static struct Stivale2_HeaderTagSmp smpHdrTag = {
    .Tag = {
        .Identifier = STIVALE2_HEADER_TAG_SMP_ID,
        .Next = 0
    },
    .Flags = 0
};

static struct Stivale2_HeaderTagFramebuffer framebufferHdrTag = {
    .Tag = {
        .Identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .Next = (uintptr_t)&smpHdrTag
    },
    .FramebufferWidth = 0,
    .FramebufferHeight = 0,
    .FramebufferBpp = 0
};

static uint8_t stack[4096] = { 0 };

__attribute__((section(".stivale2hdr"), used))
static struct Stivale2_Header stivaleHdr = {
    .EntryPoint = 0,
    .Stack = (uintptr_t)stack + sizeof(stack),
    .Flags = 0,
    .Tags = (uintptr_t)&framebufferHdrTag
};

void* Stivale2_GetTag(Stivale2_Struct* stivale2_struct, uint64_t id)
{
    Stivale2_Tag* currentTag = (Stivale2_Tag*)((void*)(stivale2_struct->Tags + PhysicalMemoryManager::KERNEL_BASE_ADDRESS));
    while (true)
    {
        if (currentTag == nullptr)
            return nullptr;

        if (currentTag->Identifier == id)
            return currentTag;

        currentTag = (Stivale2_Tag*)((void*)(currentTag->Next + PhysicalMemoryManager::KERNEL_BASE_ADDRESS));
    }
}