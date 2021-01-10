#pragma once

#include <LibC/stddef.h>

class IDT
{
private:
	static constexpr size_t EntrySize = 8;
	static constexpr size_t EntryCount = 256;

	enum TypeAttributes : uint8_t
	{
		PRESENT = 1 << 7,
		RING_3 = 1 << 5 | 1 << 6,
		TASK_GATE = 1 << 0 | 1 << 2,
		INTERRUPT_GATE = 1 << 1 | 1 << 2 | 1 << 3,
		TRAP_GATE = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3,
		RING_0 = 0b0
	};

	struct PACKED Entry
	{
		uint16_t Offset_1;
		uint16_t Selector;
		uint8_t Ist;
		uint8_t Attributes;
		uint16_t Offset_2;
		uint32_t Offset_3;
		uint32_t Zero;
	} m_Entries[EntryCount];

	struct PACKED Ptr
	{
		uint16_t Size;
		uint64_t Address;
	} m_Ptr;

	friend class IRQManager;

	static IDT m_Instance;

public:
	IDT();

	void Install();
	void CreateBasicTables();

	static IDT& Get();

private:
	friend TypeAttributes operator|(TypeAttributes left, TypeAttributes right)
	{
		return static_cast<TypeAttributes>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
	}
};