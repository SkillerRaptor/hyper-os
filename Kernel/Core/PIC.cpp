#include <Kernel/Core/PIC.h>

#include <AK/IO.h>
#include <LibC/stdio.h>

PIC PIC::m_Instance;

void PIC::ReMap(uint8_t masterOffset, uint8_t slaveOffset)
{
	static constexpr const int Icw1_Icw4 = 0x01;
	static constexpr const int Icw1_Init = 0x10;
	static constexpr const int Icw4_8086 = 0x01;

	/* Start Initialization Sequence */
	IO::Out8(MasterCommandSelector(), Icw1_Init | Icw1_Icw4);
	IO::IoWait();
	IO::Out8(SlaveCommandSelector(), Icw1_Init | Icw1_Icw4);
	IO::IoWait();

	/* Set PIC's vector offsets */
	IO::Out8(MasterDataSelector(), masterOffset);
	IO::IoWait();
	IO::Out8(SlaveDataSelector(), slaveOffset);
	IO::IoWait();

	/* Set Identity */
	IO::Out8(MasterDataSelector(), 0x04);
	IO::IoWait();
	IO::Out8(SlaveDataSelector(), 0x02);
	IO::IoWait();

	/* Set 8086 Mode */
	IO::Out8(MasterDataSelector(), Icw4_8086);
	IO::IoWait();
	IO::Out8(SlaveDataSelector(), Icw4_8086);
	IO::IoWait();
}

void PIC::Disable()
{
	static constexpr const int DisableCode = 0xFF;

	IO::Out8(SlaveCommandSelector(), DisableCode);
	IO::Out8(MasterDataSelector(), DisableCode);
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

	value = IO::In8(port) | (1 << interruptRequestLine);
	IO::Out8(port, value);
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

	value = IO::In8(port) & ~(1 << interruptRequestLine);
	IO::Out8(port, value);
}

void PIC::SendEndOfInterrupt(uint8_t interruptRequest)
{
	static constexpr const int EndOfInterruptCode = 0x20;

	if (interruptRequest >= 0x08)
		IO::Out8(SlaveCommandSelector(), EndOfInterruptCode);
	IO::Out8(MasterCommandSelector(), EndOfInterruptCode);
}

uint16_t PIC::GetInServiceRegister()
{
	static constexpr const int InServiceRegisterCode = 0x0A;

	IO::Out8(MasterCommandSelector(), InServiceRegisterCode);
	IO::Out8(SlaveCommandSelector(), InServiceRegisterCode);
	return (IO::In8(SlaveCommandSelector()) << 8) | IO::In8(MasterCommandSelector());
}

uint16_t PIC::GetInterruptRequestRegister()
{
	static constexpr const int InterruptRequestRegisterCode = 0x0B;

	IO::Out8(MasterCommandSelector(), InterruptRequestRegisterCode);
	IO::Out8(SlaveCommandSelector(), InterruptRequestRegisterCode);
	return (IO::In8(SlaveCommandSelector()) << 8) | IO::In8(MasterCommandSelector());
}

PIC& PIC::Get()
{
	return m_Instance;
}