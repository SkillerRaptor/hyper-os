#include <Kernel/Core/IDT.h>

#include <stdio.h>
#include <Kernel/Core/GDT.h>
#include <Kernel/Core/IRQManager.h>

IDT IDT::m_Instance;

IDT::IDT()
	: m_Entries(), m_Ptr({ sizeof(Entry) * EntryCount - 1, (uintptr_t)m_Entries })
{
	for (size_t i = 0; i < EntryCount; i++)
		m_Entries[i] = Entry{};
}

void IDT::Install()
{
	m_Ptr.Size = sizeof(Entry) * EntryCount - 1;

	asm("lidt %0":: "m"(m_Ptr));

	printf("[CPU] IDT ready...\n");
}

void IDT::RegisterIsr(uint16_t index, TypeAttributes attributes, ISR handler)
{
	if (!handler)
	{
		printf("[IDT] Tried to register an invalid isr at index %u\n", index); // TODO: PANIC!!!
		return;
	}

	Entry& entry = m_Entries[index];
	entry.Offset_1 = (reinterpret_cast<size_t>(handler) & 0x0000FFFF);
	entry.Offset_2 = (reinterpret_cast<size_t>(handler) & 0xFFFF0000) >> 16;
	entry.Offset_3 = (reinterpret_cast<size_t>(handler) & 0xFFFFFFFF00000000) >> 32;
	entry.Attributes = attributes;
	entry.Selector = GDT::KernelCodeSelector();

	m_Ptr.Address = (uintptr_t)m_Entries;
}

void IDT::RegisterInterruptHandler(uint16_t index, ISR handler)
{
	RegisterIsr(index, TypeAttributes::INTERRUPT_GATE | TypeAttributes::PRESENT, handler);
}

void IDT::RegisterTrapHandler(uint16_t index, ISR handler)
{
	RegisterIsr(index, TypeAttributes::TRAP_GATE | TypeAttributes::PRESENT, handler);
}

IDT& IDT::Get()
{
	return m_Instance;
}