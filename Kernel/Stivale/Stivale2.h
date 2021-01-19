#pragma once

#include <LibC/stdint.h>

struct PACKED Stivale2_Tag
{
	uint64_t Identifier;
	uint64_t Next;
};

struct PACKED Stivale2_Header
{
	uint64_t EntryPoint;
	uint64_t Stack;
	uint64_t Flags;
	uint64_t Tags;
};

#define STIVALE2_HEADER_TAG_FRAMEBUFFER_ID 0x3ecc1bc43d0f7971

#define STIVALE2_HEADER_TAG_FB_MTRR_ID 0x4c7bb07731282e00

struct PACKED Stivale2_HeaderTagFramebuffer
{
	Stivale2_Tag Tag;
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferBpp;
};

#define STIVALE2_HEADER_TAG_SMP_ID 0x1ab015085f3273df

struct PACKED Stivale2_HeaderTagSmp
{
	Stivale2_Tag Tag;
	uint64_t Flags;
};

#define STIVALE2_HEADER_TAG_5LV_PAGING_ID 0x932f477032007e8f

struct PACKED Stivale2_Struct
{
#define STIVALE2_BOOTLOADER_BRAND_SIZE 64
	char BootloaderBrand[STIVALE2_BOOTLOADER_BRAND_SIZE];

#define STIVALE2_BOOTLOADER_VERSION_SIZE 64
	char BootloaderVersion[STIVALE2_BOOTLOADER_VERSION_SIZE];

	uint64_t Tags;
};

#define STIVALE2_STRUCT_TAG_CMDLINE_ID 0xe5e76a1b4597a781

struct PACKED Stivale2_StructTagCmdline
{
	Stivale2_Tag Tag;
	uint64_t CmdLine;
};

#define STIVALE2_STRUCT_TAG_MEMMAP_ID 0x2187f79e8612de07

enum
{
	STIVALE2_MMAP_USABLE = 1,
	STIVALE2_MMAP_RESERVED = 2,
	STIVALE2_MMAP_ACPI_RECLAIMABLE = 3,
	STIVALE2_MMAP_ACPI_NVS = 4,
	STIVALE2_MMAP_BAD_MEMORY = 5,
	STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE = 0x1000,
	STIVALE2_MMAP_KERNEL_AND_MODULES = 0x1001
};

struct PACKED Stivale2_MmapEntry
{
	uint64_t Base;
	uint64_t Length;
	uint32_t Type;
	uint32_t Unused;
};

struct PACKED Stivale2_StructTagMemmap
{
	Stivale2_Tag Tag;
	uint64_t Entries;
	Stivale2_MmapEntry Memmap[];
};

#define STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID 0x506461d2950408fa

enum
{
	STIVALE2_FBUF_MMODEL_RGB = 1
};

struct PACKED Stivale2_StructTagFramebuffer
{
	Stivale2_Tag Tag;
	uint64_t FramebufferAddress;
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferPitch;
	uint16_t FramebufferBpp;
	uint8_t MemoryModel;
	uint8_t RedMaskSize;
	uint8_t RedMaskShift;
	uint8_t GreenMaskSize;
	uint8_t GreenMaskShift;
	uint8_t BlueMaskSize;
	uint8_t BlueMaskShift;
};

#define STIVALE2_STRUCT_TAG_FB_MTRR_ID 0x6bc1a78ebe871172

#define STIVALE2_STRUCT_TAG_MODULES_ID 0x4b6fe466aade04ce

struct PACKED Stivale2_Module
{
	uint64_t Begin;
	uint64_t End;

#define STIVALE2_MODULE_STRING_SIZE 128
	char String[STIVALE2_MODULE_STRING_SIZE];
};

struct PACKED Stivale2_StructTagModules
{
	Stivale2_Tag Tag;
	uint64_t ModuleCount;
	Stivale2_Module Modules[];
};

#define STIVALE2_STRUCT_TAG_RSDP_ID 0x9e1786930a375e78

struct PACKED Stivale2_StructTagRsdp
{
	Stivale2_Tag Tag;
	uint64_t Rsdp;
};

#define STIVALE2_STRUCT_TAG_EPOCH_ID 0x566a7bed888e1407

struct PACKED Stivale2_StructTagEpoch
{
	Stivale2_Tag Tag;
	uint64_t Epoch;
};

#define STIVALE2_STRUCT_TAG_FIRMWARE_ID 0x359d837855e3858c

struct PACKED Stivale2_StructTagFirmware
{
	Stivale2_Tag Tag;
	uint64_t Flags;
};

#define STIVALE2_STRUCT_TAG_SMP_ID 0x34d1d96339647025

struct PACKED Stivale2_SmpInfo
{
	uint32_t ProcessorId;
	uint32_t LapicId;
	uint64_t TargetStack;
	uint64_t GotoAddress;
	uint64_t ExtraArgument;
};

struct PACKED Stivale2_StructTagSmp
{
	Stivale2_Tag Tag;
	uint64_t Flags;
	uint32_t BspLapicId;
	uint32_t Unused;
	uint64_t CpuCount;
	Stivale2_SmpInfo SmpInfo[];
};

#define STIVALE2_STRUCT_TAG_PXE_SERVER_INFO 0x29d1e96239247032

struct PACKED Stivale2_StructTagPxeServerInfo
{
	Stivale2_Tag Tag;
	uint32_t ServerIp;
};

void* Stivale2_GetTag(Stivale2_Struct* stivale2_struct, uint64_t id);