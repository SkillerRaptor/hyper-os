#include "gdt.h"

#include <utilities/logger.h>

#include <stdint.h>

#define GDT_ACCESS_ATTRIBUTE_NULL 0x00
#define GDT_ACCESS_ATTRIBUTE_PRESENT (1 << 7)
#define GDT_ACCESS_ATTRIBUTE_RING_3 (1 << 6 | 1 << 5)
#define GDT_ACCESS_ATTRIBUTE_CODE_OR_DATA (1 << 4)
#define GDT_ACCESS_ATTRIBUTE_EXECUTABLE (1 << 3)
#define GDT_ACCESS_ATTRIBUTE_GROWS_DOWN (1 << 2)
#define GDT_ACCESS_ATTRIBUTE_ALLOW_LOWER (1 << 2)
#define GDT_ACCESS_ATTRIBUTE_READABLE (1 << 1)
#define GDT_ACCESS_ATTRIBUTE_WRITEABLE (1 << 1)

#define GDT_FLAG_ATTRIBUTE_NULL 0x00
#define GDT_FLAG_ATTRIBUTE_GRANULARITY_1B 0x00
#define GDT_FLAG_ATTRIBUTE_GRANULARITY_4K (1 << 3)
#define GDT_FLAG_ATTRIBUTE_SIZE_16_BIT 0x00
#define GDT_FLAG_ATTRIBUTE_SIZE_32_BIT (1 << 2)
#define GDT_FLAG_ATTRIBUTE_SIZE_64_BIT (1 << 1)

struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_high: 4;
	uint8_t flags: 4;
	uint8_t base_high;
} __attribute__((packed));

struct entries
{
	struct gdt_entry null_entry;
	struct gdt_entry kernel_entries[2];
	// TODO: Userland Entry
	// TODO: TSS Entry
} __attribute__((packed));

struct gdt_pointer
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct entries entries;
static struct gdt_pointer pointer;

static void gdt_create_descriptor(
	struct gdt_entry* entry,
	uint32_t base,
	uint32_t limit,
	uint8_t access,
	uint8_t flags);

void gdt_init(void)
{
	info("Initializing GDT...");
	
	/* Null Entry */
	gdt_create_descriptor(
		&entries.null_entry,
		0,
		0,
		GDT_ACCESS_ATTRIBUTE_NULL,
		GDT_FLAG_ATTRIBUTE_NULL);
	
	info(" Null descriptor created!");
	
	/* Kernel Code */
	uint8_t kernel_code_access_attributes = 0x00000000;
	kernel_code_access_attributes |= GDT_ACCESS_ATTRIBUTE_PRESENT;
	kernel_code_access_attributes |= GDT_ACCESS_ATTRIBUTE_CODE_OR_DATA;
	kernel_code_access_attributes |= GDT_ACCESS_ATTRIBUTE_EXECUTABLE;
	kernel_code_access_attributes |= GDT_ACCESS_ATTRIBUTE_READABLE;
	
	uint8_t kernel_code_flag_attributes = 0x00000000;
	kernel_code_flag_attributes |= GDT_FLAG_ATTRIBUTE_GRANULARITY_4K;
	kernel_code_flag_attributes |= GDT_FLAG_ATTRIBUTE_SIZE_64_BIT;
	
	gdt_create_descriptor(
		&entries.kernel_entries[0],
		0x00000000,
		0xFFFFFFFF,
		kernel_code_access_attributes,
		kernel_code_flag_attributes);
	
	info(" Kernel code descriptor created!");
	
	/* Kernel Data */
	uint8_t kernel_data_access_attributes = 0x00000000;
	kernel_data_access_attributes |= GDT_ACCESS_ATTRIBUTE_PRESENT;
	kernel_data_access_attributes |= GDT_ACCESS_ATTRIBUTE_CODE_OR_DATA;
	kernel_data_access_attributes |= GDT_ACCESS_ATTRIBUTE_WRITEABLE;
	
	uint8_t kernel_data_flag_attributes = 0x00000000;
	kernel_data_flag_attributes |= GDT_FLAG_ATTRIBUTE_GRANULARITY_4K;
	kernel_data_flag_attributes |= GDT_FLAG_ATTRIBUTE_SIZE_32_BIT;
	
	gdt_create_descriptor(
		&entries.kernel_entries[1],
		0x00000000,
		0xFFFFFFFF,
		kernel_data_access_attributes,
		kernel_data_flag_attributes);
	
	info(" Kernel data descriptor created!");
	
	pointer.size = sizeof(entries) - 1;
	pointer.address = (uintptr_t) &entries;
	
	gdt_reload();
	info(" GDT was reloaded!");
	
	info("Initializing GDT finished!");
}

void gdt_reload(void)
{
	asm volatile ("cli");
	
	asm volatile (
	"lgdt %0\n"
	"pushq %%rbp\n"
	"movq %%rsp, %%rbp\n"
	"pushq %1\n"
	"pushq %%rbp\n"
	"pushfq\n"
	"pushq %2\n"
	"pushq $1f\n"
	"iretq\n"
	"1:\n"
	"popq %%rbp\n"
	"mov %%ds, %1\n"
	"mov %%es, %1\n"
	"mov %%fs, %1\n"
	"mov %%gs, %1\n"
	"mov %%ss, %1\n"
	:
	: "m"(pointer), "r"((uint64_t) KERNEL_DATA_SELECTOR), "r"((uint64_t) KERNEL_CODE_SELECTOR)
	: "memory"
	);
}

static void gdt_create_descriptor(
	struct gdt_entry* entry,
	uint32_t base,
	uint32_t limit,
	uint8_t access,
	uint8_t flags)
{
	entry->base_low = base & 0x0000FFFF;
	entry->base_mid = (base & 0x00FF0000) >> 16;
	entry->base_high = (base & 0xFF000000) >> 24;
	
	entry->access = access;
	entry->flags = flags;
	
	entry->limit_low = limit & 0x0000FFFF;
	entry->limit_high = (limit & 0x000F0000) >> 16;
}