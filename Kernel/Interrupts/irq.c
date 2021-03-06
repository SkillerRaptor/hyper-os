#include <Kernel/Interrupts/irq.h>

#include <AK/io.h>
#include <AK/logger.h>
#include <Kernel/Interrupts/idt.h>
#include <Kernel/Interrupts/pic.h>

static const char* EXCEPTIONS[] = 
{
	"Divide-by-zero Error",
	"Debug",
	"Non-maskable Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Device Not Available",
	"Double Fault",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"x87 Floating-Point Exception"
	"Alignment Check",
	"Machine Check"
	"SIMD Floating-Point Exception",
	"Virtualiziation Exception",
	"Security Exception"
};

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

void irq_init(void)
{
	info("Kernel (irq.c): Registering IRQ handlers...");

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

	info("Kernel (irq.c): IRQ handlers registered!");
}

void c_interrupt_handler_0()
{
	pic_send_end_of_interrupt(0);
}

void c_interrupt_handler_1()
{
	uint8_t scanCode = io_inb(0x60);
	(void) scanCode;
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
	error("Exception: %s", EXCEPTIONS[0]);
	while (1);
}

void c_exception_handler_1()
{
	error("Exception: %s", EXCEPTIONS[1]);
	while (1);
}

void c_exception_handler_2()
{
	error("Exception: %s", EXCEPTIONS[2]);
	while (1);
}

void c_exception_handler_3()
{
	error("Exception: %s", EXCEPTIONS[3]);
	while (1);
}

void c_exception_handler_4()
{
	error("Exception: %s", EXCEPTIONS[4]);
	while (1);
}

void c_exception_handler_5()
{
	error("Exception: %s", EXCEPTIONS[5]);
	while (1);
}

void c_exception_handler_6()
{
	error("Exception: %s", EXCEPTIONS[6]);
	while (1);
}

void c_exception_handler_7()
{
	error("Exception: %s", EXCEPTIONS[7]);
	while (1);
}

void c_exception_handler_8()
{
	error("Exception: %s", EXCEPTIONS[8]);
	while (1);
}

void c_exception_handler_10()
{
	error("Exception: %s", EXCEPTIONS[9]);
	while (1);
}

void c_exception_handler_11()
{
	error("Exception: %s", EXCEPTIONS[10]);
	while (1);
}

void c_exception_handler_12()
{
	error("Exception: %s", EXCEPTIONS[11]);
	while (1);
}

void c_exception_handler_13()
{
	error("Exception: %s", EXCEPTIONS[12]);
	while (1);
}

void c_exception_handler_14()
{
	error("Exception: %s", EXCEPTIONS[13]);
	while (1);
}

void c_exception_handler_16()
{
	error("Exception: %s", EXCEPTIONS[14]);
	while (1);
}

void c_exception_handler_17()
{
	error("Exception: %s", EXCEPTIONS[15]);
	while (1);
}

void c_exception_handler_18()
{
	error("Exception: %s", EXCEPTIONS[16]);
	while (1);
}

void c_exception_handler_19()
{
	error("Exception: %s", EXCEPTIONS[17]);
	while (1);
}

void c_exception_handler_20()
{
	error("Exception: %s", EXCEPTIONS[18]);
	while (1);
}

void c_exception_handler_30()
{
	error("Exception: %s", EXCEPTIONS[19]);
	while (1);
}