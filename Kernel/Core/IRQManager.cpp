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
	RegisterInterruptRequest(32, (unsigned long)IRQCall0);

	extern int IRQCall1();
	RegisterInterruptRequest(33, (unsigned long)IRQCall1);

	extern int IRQCall2();
	RegisterInterruptRequest(34, (unsigned long)IRQCall2);

	extern int IRQCall3();
	RegisterInterruptRequest(35, (unsigned long)IRQCall3);

	extern int IRQCall4();
	RegisterInterruptRequest(36, (unsigned long)IRQCall4);

	extern int IRQCall5();
	RegisterInterruptRequest(37, (unsigned long)IRQCall5);

	extern int IRQCall6();
	RegisterInterruptRequest(38, (unsigned long)IRQCall6);

	extern int IRQCall7();
	RegisterInterruptRequest(39, (unsigned long)IRQCall7);

	extern int IRQCall8();
	RegisterInterruptRequest(40, (unsigned long)IRQCall8);

	extern int IRQCall9();
	RegisterInterruptRequest(41, (unsigned long)IRQCall9);

	extern int IRQCall10();
	RegisterInterruptRequest(42, (unsigned long)IRQCall10);

	extern int IRQCall11();
	RegisterInterruptRequest(43, (unsigned long)IRQCall11);

	extern int IRQCall12();
	RegisterInterruptRequest(44, (unsigned long)IRQCall12);

	extern int IRQCall13();
	RegisterInterruptRequest(45, (unsigned long)IRQCall13);

	extern int IRQCall14();
	RegisterInterruptRequest(46, (unsigned long)IRQCall14);

	extern int IRQCall15();
	RegisterInterruptRequest(47, (unsigned long)IRQCall15);
}
__END_DECLS

void IRQManager::RegisterInterruptRequest(size_t index, unsigned long address)
{
	static constexpr const int InterruptGateCode = 0x8E;
	IDT::Entry* entries = IDT::Get().GetEntries();
	entries[index].OffsetLow = address & 0xFFFF;
	entries[index].Selector = GDT::KernelCodeSelector();
	entries[index].Zero = 0;
	entries[index].Type = IDT::TypeAttributes::INTERRUPT_GATE;
	entries[index].OffsetHigh = (address & 0xFFFF0000) >> 16;
}

IRQManager& IRQManager::Get()
{
	return m_Instance;
}

__BEGIN_DECLS
void IRQHandler(uint16_t interruptRequestLine)
{
	printf("Triggered %u IRQ Line\n", interruptRequestLine);
	PIC::Get().SendEndOfInterrupt(interruptRequestLine);
}
__END_DECLS