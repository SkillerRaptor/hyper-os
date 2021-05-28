#include "gdt.h"

#include <lib/logger.h>

#include <stdint.h>

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

struct gdt_entries
{
	struct gdt_entry null_entry;
	struct gdt_entry kernel_entries[2];
	struct gdt_entry userland_entries[2];
	// TODO: TSS Entry
};

struct gdt_pointer
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct gdt_entries entries;
static struct gdt_pointer pointer;

static void gdt_create_descriptor(struct gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void gdt_init(void)
{
	info("GDT: Initializing...");
	
	gdt_create_descriptor( &entries.null_entry, 0x00000000, 0x00000000, 0x00, 0x00);
	
	gdt_create_descriptor(&entries.kernel_entries[0], 0x00000000, 0xFFFFFFFF, 0x9A, 0x0A);
	gdt_create_descriptor(&entries.kernel_entries[1], 0x00000000, 0xFFFFFFFF, 0x92, 0x0C);
	
	pointer.size = sizeof(entries) - 1;
	pointer.address = (uintptr_t) &entries;
	
	gdt_reload();
	
	info("GDT: Initializing finished!");
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

static void gdt_create_descriptor(struct gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	entry->base_low = base & 0x0000FFFF;
	entry->base_mid = (base & 0x00FF0000) >> 16;
	entry->base_high = (base & 0xFF000000) >> 24;
	
	entry->access = access;
	entry->flags = flags;
	
	entry->limit_low = limit & 0x0000FFFF;
	entry->limit_high = (limit & 0x000F0000) >> 16;
}
