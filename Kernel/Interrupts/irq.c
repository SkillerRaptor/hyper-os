#include <Kernel/Interrupts/irq.h>

#include <AK/io.h>
#include <AK/logger.h>
#include <Kernel/Interrupts/idt.h>
#include <Kernel/Interrupts/pic.h>

void interrupt_handler_0();
void interrupt_handler_1();
void interrupt_handler_2();
void interrupt_handler_3();
void interrupt_handler_4();
void interrupt_handler_5();
void interrupt_handler_6();
void interrupt_handler_7();
void interrupt_handler_8();
void interrupt_handler_9();
void interrupt_handler_10();
void interrupt_handler_11();
void interrupt_handler_12();
void interrupt_handler_13();
void interrupt_handler_14();
void interrupt_handler_15();

void exception_handler_8();
void exception_handler_13();

void irq_init(void)
{
	idt_register_interrupt_handler(32 + 0, interrupt_handler_0);
	idt_register_interrupt_handler(32 + 1, interrupt_handler_1);
	idt_register_interrupt_handler(32 + 2, interrupt_handler_2);
	idt_register_interrupt_handler(32 + 3, interrupt_handler_3);
	idt_register_interrupt_handler(32 + 4, interrupt_handler_4);
	idt_register_interrupt_handler(32 + 5, interrupt_handler_5);
	idt_register_interrupt_handler(32 + 6, interrupt_handler_6);
	idt_register_interrupt_handler(32 + 7, interrupt_handler_7);
	idt_register_interrupt_handler(32 + 8, interrupt_handler_8);
	idt_register_interrupt_handler(32 + 9, interrupt_handler_9);
	idt_register_interrupt_handler(32 + 10, interrupt_handler_10);
	idt_register_interrupt_handler(32 + 11, interrupt_handler_11);
	idt_register_interrupt_handler(32 + 12, interrupt_handler_12);
	idt_register_interrupt_handler(32 + 13, interrupt_handler_13);
	idt_register_interrupt_handler(32 + 14, interrupt_handler_14);
	idt_register_interrupt_handler(32 + 15, interrupt_handler_15);

	idt_register_trap_handler(0x8, exception_handler_8);
	idt_register_trap_handler(0xD, exception_handler_13);

	info("The IRQ handlers were registered!");
}

void interrupt_handler_0()
{
	debug("0");
	pic_send_end_of_interrupt(0);
}

void interrupt_handler_1()
{
	debug("PRESSED!!!");
	uint8_t scanCode = io_inb(0x60);
	debug("READ");
	pic_send_end_of_interrupt(1);
}

void interrupt_handler_2()
{
	pic_send_end_of_interrupt(2);
}

void interrupt_handler_3()
{
	pic_send_end_of_interrupt(3);
}

void interrupt_handler_4()
{
	pic_send_end_of_interrupt(4);
}

void interrupt_handler_5()
{
	pic_send_end_of_interrupt(5);
}

void interrupt_handler_6()
{
	pic_send_end_of_interrupt(6);
}

void interrupt_handler_7()
{
	pic_send_end_of_interrupt(7);
}

void interrupt_handler_8()
{
	pic_send_end_of_interrupt(8);
}

void interrupt_handler_9()
{
	pic_send_end_of_interrupt(9);
}

void interrupt_handler_10()
{
	pic_send_end_of_interrupt(10);
}

void interrupt_handler_11()
{
	pic_send_end_of_interrupt(11);
}

void interrupt_handler_12()
{
	pic_send_end_of_interrupt(12);
}

void interrupt_handler_13()
{
	pic_send_end_of_interrupt(13);
}

void interrupt_handler_14()
{
	pic_send_end_of_interrupt(14);
}

void interrupt_handler_15()
{
	pic_send_end_of_interrupt(15);
}

void exception_handler_8()
{

}

void exception_handler_13()
{

}
