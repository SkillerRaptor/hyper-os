#pragma once

#include <LibC/stdint.h>

struct PACKED StivaleHeader 
{
	uint64_t Stack;
	uint16_t Flags; // 0 = Text Mode | 1 = Graphics Mode
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferBpp;
	uint64_t EntryPoint;
};

struct PACKED StivaleModule 
{
	uint64_t Begin;
	uint64_t End;
	char String[128];
	uint64_t Next;
};

enum StivaleMemoryType 
{
	USABLE = 1,
	RESERVED = 2,
	ACPI_RECLAIMABLE = 3,
	ACPI_NVS = 4,
	BAD_MEMORY = 5,
	KERNEL_AND_MODULES = 10
};

struct PACKED StivaleMemoryMapEntry 
{
	uint64_t Base;
	uint64_t Length;
	uint32_t Type;
	uint32_t Unused;
};

struct PACKED StivaleStruct 
{
	uint64_t Cmdline;
	uint64_t MemoryMapAddress;
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