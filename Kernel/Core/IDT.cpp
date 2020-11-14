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
	m_Ptr.Size = sizeof(Entry) * EntryCount - 1;
	m_Ptr.Address = (uint32_t)m_Entries;

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

/*
void IDT::CreateDescriptor(uint32_t base, uint32_t limit, AccessAttributes accessAttributes, FlagAttributes flagAttributes)
{
	auto& entry = NewEntry();

	entry.BaseLower = base & 0x0000FFFF;
	entry.BaseMiddle = (base & 0x00FF0000) >> 16;
	entry.BaseUpper = (base & 0xFF000000) >> 24;

	entry.Access = accessAttributes;
	entry.Flags = flagAttributes;

	entry.LimitLower = limit & 0x0000FFFF;
	entry.LimitUpper = (limit & 0x000F0000) >> 16;
}
*/

IDT& IDT::Get()
{
	return m_Instance;
}