#include "IRQManager.h"

#include <AK/IO.h>
#include <Kernel/Core/GDT.h>
#include <Kernel/Core/IDT.h>
#include <Kernel/Core/PIC.h>
#include <LibC/stdio.h>

__BEGIN_DECLS
void IRQHandler0();
void IRQHandler1();
void IRQHandler2();
void IRQHandler3();
void IRQHandler4();
void IRQHandler5();
void IRQHandler6();
void IRQHandler7();
void IRQHandler8();
void IRQHandler9();
void IRQHandler10();
void IRQHandler11();
void IRQHandler12();
void IRQHandler13();
void IRQHandler14();
void IRQHandler15();
__END_DECLS

void IRQManager::Install()
{
	IDT& idt = IDT::Get();

	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 0, IRQHandler0);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 1, IRQHandler1);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 2, IRQHandler2);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 3, IRQHandler3);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 4, IRQHandler4);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 5, IRQHandler5);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 6, IRQHandler6);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 7, IRQHandler7);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 8, IRQHandler8);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 9, IRQHandler9);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 10, IRQHandler10);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 11, IRQHandler11);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 12, IRQHandler12);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 13, IRQHandler13);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 14, IRQHandler14);
	idt.RegisterInterruptHandler(IRQ_BASE_INDEX + 15, IRQHandler15);
}

__BEGIN_DECLS
void IRQHandler0()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(0);
}

void IRQHandler1()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(1);
}

void IRQHandler2()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(2);
}

void IRQHandler3()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(3);
}

void IRQHandler4()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(4);
}

void IRQHandler5()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(5);
}

void IRQHandler6()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(6);
}

void IRQHandler7()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(7);
}

void IRQHandler8()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(8);
}

void IRQHandler9()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(9);
}

void IRQHandler10()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(10);
}

void IRQHandler11()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(11);
}

void IRQHandler12()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(12);
}

void IRQHandler13()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(13);
}

void IRQHandler14()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(14);
}

void IRQHandler15()
{
	printf("LINE!\n");
	PIC::Get().SendEndOfInterrupt(15);
}
__END_DECLS