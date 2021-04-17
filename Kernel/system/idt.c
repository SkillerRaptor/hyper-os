#include "idt.h"

#include "gdt.h"
#include "io_service.h"
#include "pic.h"
#include "pit.h"

#include <drivers/ps2/ps2_keyboard.h>
#include <utilities/logger.h>

#include <stddef.h>
#include <stdint.h>

#define IDT_TYPE_PRESENT 1 << 7
#define IDT_TYPE_INTERRUPT_GATE 1 << 1 | 1 << 2 | 1 << 3
#define IDT_TYPE_TRAP_GATE 1 << 0 | 1 << 1 | 1<< 2 | 1 << 3

struct idt_entry
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t attributes;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
} __attribute__((packed));

struct idt_pointer
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct idt_entry entries[256];

static void idt_register_handler(size_t index, uint8_t flags, uintptr_t handler);
static void idt_register_interrupt_handler(size_t index, uintptr_t handler);
static void idt_register_trap_handler(size_t index, uintptr_t handler);

extern int interrupt_handler_0();
extern int interrupt_handler_1();
extern int interrupt_handler_2();
extern int interrupt_handler_3();
extern int interrupt_handler_4();
extern int interrupt_handler_5();
extern int interrupt_handler_6();
extern int interrupt_handler_7();
extern int interrupt_handler_8();
extern int interrupt_handler_9();
extern int interrupt_handler_10();
extern int interrupt_handler_11();
extern int interrupt_handler_12();
extern int interrupt_handler_13();
extern int interrupt_handler_14();
extern int interrupt_handler_15();

extern int exception_handler_0();
extern int exception_handler_1();
extern int exception_handler_2();
extern int exception_handler_3();
extern int exception_handler_4();
extern int exception_handler_5();
extern int exception_handler_6();
extern int exception_handler_7();
extern int exception_handler_8();
extern int exception_handler_10();
extern int exception_handler_11();
extern int exception_handler_12();
extern int exception_handler_13();
extern int exception_handler_14();
extern int exception_handler_16();
extern int exception_handler_17();
extern int exception_handler_18();
extern int exception_handler_19();
extern int exception_handler_20();
extern int exception_handler_30();

void idt_init(void)
{
	info("Initializing IDT...");
	
	/* Register Interrupt Handler */
	idt_register_interrupt_handler(32 + 0, (uintptr_t) interrupt_handler_0);
	idt_register_interrupt_handler(32 + 1, (uintptr_t) interrupt_handler_1);
	idt_register_interrupt_handler(32 + 2, (uintptr_t) interrupt_handler_2);
	idt_register_interrupt_handler(32 + 3, (uintptr_t) interrupt_handler_3);
	idt_register_interrupt_handler(32 + 4, (uintptr_t) interrupt_handler_4);
	idt_register_interrupt_handler(32 + 5, (uintptr_t) interrupt_handler_5);
	idt_register_interrupt_handler(32 + 6, (uintptr_t) interrupt_handler_6);
	idt_register_interrupt_handler(32 + 7, (uintptr_t) interrupt_handler_7);
	idt_register_interrupt_handler(32 + 8, (uintptr_t) interrupt_handler_8);
	idt_register_interrupt_handler(32 + 9, (uintptr_t) interrupt_handler_9);
	idt_register_interrupt_handler(32 + 10, (uintptr_t) interrupt_handler_10);
	idt_register_interrupt_handler(32 + 11, (uintptr_t) interrupt_handler_11);
	idt_register_interrupt_handler(32 + 12, (uintptr_t) interrupt_handler_12);
	idt_register_interrupt_handler(32 + 13, (uintptr_t) interrupt_handler_13);
	idt_register_interrupt_handler(32 + 14, (uintptr_t) interrupt_handler_14);
	idt_register_interrupt_handler(32 + 15, (uintptr_t) interrupt_handler_15);
	info(" Interrupt handler registered!");
	
	/* Register Trap Handler */
	idt_register_trap_handler(0, (uintptr_t) exception_handler_0);
	idt_register_trap_handler(1, (uintptr_t) exception_handler_1);
	idt_register_trap_handler(2, (uintptr_t) exception_handler_2);
	idt_register_trap_handler(3, (uintptr_t) exception_handler_3);
	idt_register_trap_handler(4, (uintptr_t) exception_handler_4);
	idt_register_trap_handler(5, (uintptr_t) exception_handler_5);
	idt_register_trap_handler(6, (uintptr_t) exception_handler_6);
	idt_register_trap_handler(7, (uintptr_t) exception_handler_7);
	idt_register_trap_handler(8, (uintptr_t) exception_handler_8);
	idt_register_trap_handler(10, (uintptr_t) exception_handler_10);
	idt_register_trap_handler(11, (uintptr_t) exception_handler_11);
	idt_register_trap_handler(12, (uintptr_t) exception_handler_12);
	idt_register_trap_handler(13, (uintptr_t) exception_handler_13);
	idt_register_trap_handler(14, (uintptr_t) exception_handler_14);
	idt_register_trap_handler(16, (uintptr_t) exception_handler_16);
	idt_register_trap_handler(17, (uintptr_t) exception_handler_17);
	idt_register_trap_handler(18, (uintptr_t) exception_handler_18);
	idt_register_trap_handler(19, (uintptr_t) exception_handler_19);
	idt_register_trap_handler(20, (uintptr_t) exception_handler_20);
	idt_register_trap_handler(30, (uintptr_t) exception_handler_30);
	info(" Trap handler registered!");
	
	idt_reload();
	info(" IDT was reloaded!");
	
	info("Initializing IDT finished!");
}

void idt_reload(void)
{
	struct idt_pointer pointer =
		{
			sizeof(entries) - 1,
			(uintptr_t) entries
		};
	
	/* Reloading IDT with new data */
	asm volatile (
	"lidt %0"
	:
	: "m"(pointer)
	);
}

static void idt_register_handler(size_t index, uint8_t flags, uintptr_t handler)
{
	entries[index].offset_low = (handler & 0x0000FFFF) >> 0;
	entries[index].selector = KERNEL_CODE_SELECTOR;
	entries[index].ist = 0x0;
	entries[index].attributes = flags;
	entries[index].offset_mid = (handler & 0xFFFF0000) >> 16;
	entries[index].offset_high = (handler & 0xFFFFFFFF00000000) >> 32;
	entries[index].zero = 0;
}

static void idt_register_interrupt_handler(size_t index, uintptr_t handler)
{
	idt_register_handler(index, IDT_TYPE_PRESENT | IDT_TYPE_INTERRUPT_GATE, handler);
}

static void idt_register_trap_handler(size_t index, uintptr_t handler)
{
	idt_register_handler(index, IDT_TYPE_PRESENT | IDT_TYPE_TRAP_GATE, handler);
}

void c_interrupt_handler_0()
{
	pit_handle_tick();
	pic_send_end_of_interrupt(0);
}

void c_interrupt_handler_1()
{
	ps2_keyboard_handle_action();
	pic_send_end_of_interrupt(1);
}

void c_interrupt_handler_2()
{
	pic_send_end_of_interrupt(2);
}

void c_interrupt_handler_3()
{
	pic_send_end_of_interrupt(3);
}

void c_interrupt_handler_4()
{
	pic_send_end_of_interrupt(4);
}

void c_interrupt_handler_5()
{
	pic_send_end_of_interrupt(5);
}

void c_interrupt_handler_6()
{
	pic_send_end_of_interrupt(6);
}

void c_interrupt_handler_7()
{
	pic_send_end_of_interrupt(7);
}

void c_interrupt_handler_8()
{
	pic_send_end_of_interrupt(8);
}

void c_interrupt_handler_9()
{
	pic_send_end_of_interrupt(9);
}

void c_interrupt_handler_10()
{
	pic_send_end_of_interrupt(10);
}

void c_interrupt_handler_11()
{
	pic_send_end_of_interrupt(11);
}

void c_interrupt_handler_12()
{
	pic_send_end_of_interrupt(12);
}

void c_interrupt_handler_13()
{
	pic_send_end_of_interrupt(13);
}

void c_interrupt_handler_14()
{
	pic_send_end_of_interrupt(14);
}

void c_interrupt_handler_15()
{
	pic_send_end_of_interrupt(15);
}

void c_exception_handler_0()
{
	error("Exception handler 0 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_1()
{
	error("Exception handler 1 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_2()
{
	error("Exception handler 2 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_3()
{
	error("Exception handler 3 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_4()
{
	error("Exception handler 4 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_5()
{
	error("Exception handler 5 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_6()
{
	error("Exception handler 6 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_7()
{
	error("Exception handler 7 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_8()
{
	error("Exception handler 8 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_10()
{
	error("Exception handler 10 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_11()
{
	error("Exception handler 11 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_12()
{
	error("Exception handler 12 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_13()
{
	error("Exception handler 13 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_14()
{
	error("Exception handler 14 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_16()
{
	error("Exception handler 16 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_17()
{
	error("Exception handler 17 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_18()
{
	error("Exception handler 18 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_19()
{
	error("Exception handler 19 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_20()
{
	error("Exception handler 20 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}

void c_exception_handler_30()
{
	error("Exception handler 30 was triggered!");
	for (;;)
	{
		asm ("cli");
		asm ("hlt");
	}
}