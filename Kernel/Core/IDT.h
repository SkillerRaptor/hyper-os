#pragma once

#include <LibC/stddef.h>

class IDT
{
public:
	enum TypeAttributes : uint8_t
	{
		PRESENT = 1 << 7,
		RING_3 = 1 << 5 | 1 << 6,
		TASK_GATE = 1 << 0 | 1 << 2,
		INTERRUPT_GATE = 1 << 1 | 1 << 2 | 1 << 3,
		TRAP_GATE = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3,
		RING_0 = 0b0
	};

	friend TypeAttributes operator|(TypeAttributes left, TypeAttributes right)
	{
		return static_cast<TypeAttributes>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
	}

	struct PACKED Entry
	{
		uint16_t OffsetLow;
		uint16_t Selector;
		uint8_t Zero;
		uint8_t Type;
		uint16_t OffsetHigh;
	};

private:
	static constexpr size_t EntrySize = 8;
	static constexpr size_t EntryCount = 256;

	Entry m_Entries[EntryCount];

	struct PACKED Ptr
	{
		uint16_t Size;
		uint64_t Address;
	};

	Ptr m_Ptr;

	static IDT m_Instance;

public:
	IDT();

	void Install();
	void CreateBasicTables();

	Entry* GetEntries();

	static IDT& Get();
};