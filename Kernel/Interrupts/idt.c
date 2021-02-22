#include <Kernel/Interrupts/idt.h>

#include <AK/logger.h>
#include <Kernel/Core/gdt.h>

typedef struct
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __PACKED idt_entry_t;

typedef struct
{
    uint16_t size;
    uint64_t address;
} __PACKED idt_pointer_t;

static idt_entry_t idt_entries[256];

void idt_init(void)
{
	idt_reload();
}

void idt_reload(void)
{
	info("IDT: Loading IDT...");

	idt_pointer_t idt_pointer =
	{
		sizeof(idt_entries) - 1,
		(uintptr_t)idt_entries
	};

	asm volatile (
		"lidt %0"
		:
	: "m"(idt_pointer)
		);

	info("IDT: IDT was loaded!");
}

void idt_register_handler(size_t index, uint8_t flags, uintptr_t handler)
{
   idt_entries[index].offset_low = (handler & 0x0000FFFF) >> 0;
   idt_entries[index].selector = KERNEL_CODE_SELECTOR;
   idt_entries[index].ist = 0x0;
   idt_entries[index].attributes = flags;
   idt_entries[index].offset_mid = (handler & 0xFFFF0000) >> 16;
   idt_entries[index].offset_high = (handler& 0xFFFFFFFF00000000) >> 32;
   idt_entries[index].zero = 0;
}

void idt_register_interrupt_handler(size_t index, uintptr_t handler)
{
	idt_register_handler(index, IDT_TYPE_PRESENT | IDT_TYPE_INTERRUPT_GATE, handler);
}

void idt_register_trap_handler(size_t index, uintptr_t handler)
{
	idt_register_handler(index, IDT_TYPE_PRESENT | IDT_TYPE_TRAP_GATE, handler);
}