#include "IDT.h"

#include <LibC/stdio.h>

#include "IRQManager.hpp"

IDT IDT::m_Instance;

IDT::IDT()
	: m_Entries(), m_Ptr({ EntryCount, (uintptr_t) m_Entries })
{
	for (size_t i = 0; i < EntryCount; i++)
		m_Entries[i] = Entry{};
}

void IDT::Install()
{
	m_Ptr.Address = (uintptr_t)m_Entries;
	m_Ptr.Size = sizeof(Entry) * EntryCount - 1;

	asm volatile("lidt %0\n"
		"sti\n"
		:: "m"(m_Ptr)
		);

	printf("[CPU] IDT ready...\n");
}

void IDT::CreateBasicTables()
{
	IRQManager::Get().RegisterBasicInterrupts();
}

IDT& IDT::Get()
{
	return m_Instance;
}