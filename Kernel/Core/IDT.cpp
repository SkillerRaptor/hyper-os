#include "IDT.h"

#include <LibC/stdio.h>

#include "IRQManager.hpp"

IDT IDT::m_Instance;

IDT::IDT()
	: m_Entries(), m_Ptr({ EntryCount, (uint32_t) m_Entries })
{
	for (size_t i = 0; i < EntryCount; i++)
		m_Entries[i] = Entry{};
}

void IDT::Install()
{
	m_Ptr.Address = (uint32_t)m_Entries;
	m_Ptr.Size = sizeof(m_Entries) - 1;

	asm volatile("lidt %0\n"
		"sti\n"
		:: "m"(m_Ptr)
		);
}

void IDT::CreateBasicTables()
{
	IRQManager::Get().RegisterBasicInterrupts();
}

IDT::Entry* IDT::GetEntries()
{
	return m_Entries;
}

IDT& IDT::Get()
{
	return m_Instance;
}