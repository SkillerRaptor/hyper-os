#include <Kernel/Core/IRQManager.h>

#include <stdio.h>
#include <AK/IO.h>
#include <AK/Panic.h>
#include <Kernel/Core/GDT.h>
#include <Kernel/Core/IDT.h>
#include <Kernel/Core/PIC.h>

__BEGIN_DECLS
void ExceptionHandler8();
void ExceptionHandler13();
void ExceptionHandler14();

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

	idt.RegisterTrapHandler(0x8, ExceptionHandler8);
	idt.RegisterTrapHandler(0xD, ExceptionHandler13);
	idt.RegisterTrapHandler(0xE, ExceptionHandler14);

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
void ExceptionHandler8()
{
	panic("IRQManager: Double Fault!");
}

void ExceptionHandler13()
{
	panic("IRQManager: General Protection Fault!");
}

void ExceptionHandler14()
{
	panic("IRQManager: Page Fault!");
}

void IRQHandler0()
{
	printf("IRQ 0!\n");
	PIC::Get().SendEndOfInterrupt(0);
}

void IRQHandler1()
{
	printf("IRQ 1!\n");
	PIC::Get().SendEndOfInterrupt(1);
}

void IRQHandler2()
{
	printf("IRQ 2!\n");
	PIC::Get().SendEndOfInterrupt(2);
}

void IRQHandler3()
{
	printf("IRQ 3!\n");
	PIC::Get().SendEndOfInterrupt(3);
}

void IRQHandler4()
{
	printf("IRQ 4!\n");
	PIC::Get().SendEndOfInterrupt(4);
}

void IRQHandler5()
{
	printf("IRQ 5!\n");
	PIC::Get().SendEndOfInterrupt(5);
}

void IRQHandler6()
{
	printf("IRQ 6!\n");
	PIC::Get().SendEndOfInterrupt(6);
}

void IRQHandler7()
{
	printf("IRQ 7!\n");
	PIC::Get().SendEndOfInterrupt(7);
}

void IRQHandler8()
{
	printf("IRQ 8!\n");
	PIC::Get().SendEndOfInterrupt(8);
}

void IRQHandler9()
{
	printf("IRQ 9\n");
	PIC::Get().SendEndOfInterrupt(9);
}

void IRQHandler10()
{
	printf("IRQ 10!\n");
	PIC::Get().SendEndOfInterrupt(10);
}

void IRQHandler11()
{
	printf("IRQ 11!\n");
	PIC::Get().SendEndOfInterrupt(11);
}

void IRQHandler12()
{
	printf("IRQ 12!\n");
	PIC::Get().SendEndOfInterrupt(12);
}

void IRQHandler13()
{
	printf("IRQ 13!\n");
	PIC::Get().SendEndOfInterrupt(13);
}

void IRQHandler14()
{
	printf("IRQ 14!\n");
	PIC::Get().SendEndOfInterrupt(14);
}

void IRQHandler15()
{
	printf("IRQ 15!\n");
	PIC::Get().SendEndOfInterrupt(15);
}
__END_DECLS