#include <Kernel/Core/PIC.h>

#include <stdio.h>
#include <AK/IO.h>

PIC PIC::m_Instance;

void PIC::ReMap(uint8_t masterOffset, uint8_t slaveOffset)
{
	static constexpr const int Icw1_Icw4 = 0x01;
	static constexpr const int Icw1_Init = 0x10;
	static constexpr const int Icw4_8086 = 0x01;

	/* Start Initialization Sequence */
	IO::out8(MasterCommandSelector(), Icw1_Init | Icw1_Icw4);
	IO::wait();
	IO::out8(SlaveCommandSelector(), Icw1_Init | Icw1_Icw4);
	IO::wait();

	/* Set PIC's vector offsets */
	IO::out8(MasterDataSelector(), masterOffset);
	IO::wait();
	IO::out8(SlaveDataSelector(), slaveOffset);
	IO::wait();

	/* Set Identity */
	IO::out8(MasterDataSelector(), 0x04);
	IO::wait();
	IO::out8(SlaveDataSelector(), 0x02);
	IO::wait();

	/* Set 8086 Mode */
	IO::out8(MasterDataSelector(), Icw4_8086);
	IO::wait();
	IO::out8(SlaveDataSelector(), Icw4_8086);
	IO::wait();
}

void PIC::Disable()
{
	static constexpr const int DisableCode = 0xFF;

	IO::out8(SlaveCommandSelector(), DisableCode);
	IO::out8(MasterDataSelector(), DisableCode);
}

void PIC::SetInterruptRequestMask(uint8_t interruptRequestLine)
{
	uint16_t port;
	uint8_t value;

	if (interruptRequestLine < 8)
	{
		port = MasterDataSelector();
	}
	else
	{
		port = SlaveDataSelector();
		interruptRequestLine -= 8;
	}

	value = IO::in8(port) | (1 << interruptRequestLine);
	IO::out8(port, value);
}

void PIC::ClearInterruptRequestMask(uint8_t interruptRequestLine)
{
	uint16_t port;
	uint8_t value;

	if (interruptRequestLine < 8)
	{
		port = MasterDataSelector();
	}
	else
	{
		port = SlaveDataSelector();
		interruptRequestLine -= 8;
	}

	value = IO::in8(port) & ~(1 << interruptRequestLine);
	IO::out8(port, value);
}

void PIC::SendEndOfInterrupt(uint8_t interruptRequest)
{
	static constexpr const int EndOfInterruptCode = 0x20;

	if (interruptRequest >= 0x08)
		IO::out8(SlaveCommandSelector(), EndOfInterruptCode);
	IO::out8(MasterCommandSelector(), EndOfInterruptCode);
}

uint16_t PIC::GetInServiceRegister()
{
	static constexpr const int InServiceRegisterCode = 0x0A;

	IO::out8(MasterCommandSelector(), InServiceRegisterCode);
	IO::out8(SlaveCommandSelector(), InServiceRegisterCode);
	return (IO::in8(SlaveCommandSelector()) << 8) | IO::in8(MasterCommandSelector());
}

uint16_t PIC::GetInterruptRequestRegister()
{
	static constexpr const int InterruptRequestRegisterCode = 0x0B;

	IO::out8(MasterCommandSelector(), InterruptRequestRegisterCode);
	IO::out8(SlaveCommandSelector(), InterruptRequestRegisterCode);
	return (IO::in8(SlaveCommandSelector()) << 8) | IO::in8(MasterCommandSelector());
}

PIC& PIC::Get()
{
	return m_Instance;
}