#pragma once

#include <LibC/stdint.h>

struct PACKED StivaleHeader {
	uint64_t Stack;
	uint16_t Flags; // 0 = Text Mode | 1 = Graphics Mode
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferBpp;
	uint64_t EntryPoint;
};

struct PACKED StivaleModule {
	uint64_t Begin;
	uint64_t End;
	char String[128];
	uint64_t Next;
};

struct PACKED StivaleStruct {
	uint64_t Cmdline;
	uint64_t MemoryMapAddr;
	uint64_t MemoryMapEntries;
	uint64_t FramebufferAddr;
	uint16_t FramebufferPitch;
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferBpp;
	uint64_t Rsdp;
	uint64_t ModuleCount;
	uint64_t Modules;
	uint64_t Epoch;
	uint64_t Flags;
};