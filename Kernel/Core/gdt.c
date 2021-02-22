#include <Kernel/Core/gdt.h>

#include <stddef.h>
#include <stdint.h>
#include <AK/logger.h>

struct GDT_Entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __PACKED;

struct GDT_Entries
{
	struct GDT_Entry entries[3];
	// TODO: TSS Entry
} __PACKED;

struct GDT_Pointer
{
	uint16_t size;
	uint64_t address;
} __PACKED;

static struct GDT_Entries gdt_entries;
static struct GDT_Pointer gdt_pointer;

void gdt_init(void)
{
	gdt_entries.entries[0].limit_low = 0;
	gdt_entries.entries[0].base_low = 0;
	gdt_entries.entries[0].base_mid = 0;
	gdt_entries.entries[0].access = 0;
	gdt_entries.entries[0].granularity = 0;
	gdt_entries.entries[0].base_high = 0;

	/* Kernel Code */
	gdt_entries.entries[1].limit_low = 0;
	gdt_entries.entries[1].base_low = 0;
	gdt_entries.entries[1].base_mid = 0;
	gdt_entries.entries[1].access = 0b10011010;
	gdt_entries.entries[1].granularity = 0b00100000;
	gdt_entries.entries[1].base_high = 0;

	/* Kernel Data */
	gdt_entries.entries[2].limit_low = 0;
	gdt_entries.entries[2].base_low = 0;
	gdt_entries.entries[2].base_mid = 0;
	gdt_entries.entries[2].access = 0b10010010;
	gdt_entries.entries[2].granularity = 0;
	gdt_entries.entries[2].base_high = 0;

	gdt_pointer.size = sizeof(gdt_entries) - 1;
	gdt_pointer.address = (uintptr_t)&gdt_entries;

	gdt_reload();
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
	: "m"(gdt_pointer), "r"((uint64_t)KERNEL_DATA_SELECTOR), "r"((uint64_t)KERNEL_CODE_SELECTOR)
		: "memory"
		);
		
	info("The GDT was installed!");
}
