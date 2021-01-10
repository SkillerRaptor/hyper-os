#include "IRQManager.hpp"

#include <LibC/stdio.h>

#include "GDT.h"
#include "IDT.h"
#include "PIC.h"

IRQManager IRQManager::m_Instance;

__BEGIN_DECLS
void IRQManager::RegisterBasicInterrupts()
{
	extern int IRQCall0();
	RegisterInterruptRequest(32, (uint64_t) IRQCall0);

	extern int IRQCall1();
	RegisterInterruptRequest(33, (uint64_t) IRQCall1);

	extern int IRQCall2();
	RegisterInterruptRequest(34, (uint64_t) IRQCall2);

	extern int IRQCall3();
	RegisterInterruptRequest(35, (uint64_t) IRQCall3);

	extern int IRQCall4();
	RegisterInterruptRequest(36, (uint64_t) IRQCall4);

	extern int IRQCall5();
	RegisterInterruptRequest(37, (uint64_t) IRQCall5);

	extern int IRQCall6();
	RegisterInterruptRequest(38, (uint64_t) IRQCall6);

	extern int IRQCall7();
	RegisterInterruptRequest(39, (uint64_t) IRQCall7);

	extern int IRQCall8();
	RegisterInterruptRequest(40, (uint64_t) IRQCall8);

	extern int IRQCall9();
	RegisterInterruptRequest(41, (uint64_t) IRQCall9);

	extern int IRQCall10();
	RegisterInterruptRequest(42, (uint64_t) IRQCall10);

	extern int IRQCall11();
	RegisterInterruptRequest(43, (uint64_t) IRQCall11);

	extern int IRQCall12();
	RegisterInterruptRequest(44, (uint64_t) IRQCall12);

	extern int IRQCall13();
	RegisterInterruptRequest(45, (uint64_t) IRQCall13);

	extern int IRQCall14();
	RegisterInterruptRequest(46, (uint64_t) IRQCall14);

	extern int IRQCall15();
	RegisterInterruptRequest(47, (uint64_t) IRQCall15);
}
__END_DECLS

void IRQManager::RegisterInterruptRequest(size_t index, uint64_t address)
{
	IDT::Entry& entry = IDT::Get().m_Entries[index];
	entry.Offset_1 = (address & 0x0000FFFF);
	entry.Offset_2 = (address & 0xFFFF0000) >> 16;
	entry.Offset_3 = (address & 0xFFFFFFFF00000000) >> 32;

	entry.Attributes = IDT::TypeAttributes::PRESENT | IDT::TypeAttributes::INTERRUPT_GATE;
	entry.Selector = GDT::KernelCodeSelector();
	entry.Zero = 0;
}

IRQManager& IRQManager::Get()
{
	return m_Instance;
}

__BEGIN_DECLS
void IRQHandler(uint16_t interruptRequestLine)
{
	PIC::Get().SendEndOfInterrupt(interruptRequestLine);
}
__END_DECLS