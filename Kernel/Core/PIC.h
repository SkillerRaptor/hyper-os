#pragma once

#include <LibC/stdint.h>

class PIC
{
private:
	static PIC m_Instance;

public:
    void ReMap(uint8_t masterOffset, uint8_t slaveOffset);
    void Disable();

	void SetInterruptRequestMask(uint8_t interruptRequestLine);
	void ClearInterruptRequestMask(uint8_t interruptRequestLine);

    void SendEndOfInterrupt(uint8_t interruptRequest);

    uint16_t GetInServiceRegister();
	uint16_t GetInterruptRequestRegister();

	static PIC& Get();

private:
	static constexpr uint16_t MasterCommandSelector() { return 0x20; }
	static constexpr uint16_t MasterDataSelector() { return 0x21; }

	static constexpr uint16_t SlaveCommandSelector() { return 0xA0; }
	static constexpr uint16_t SlaveDataSelector() { return 0xA1; }
};