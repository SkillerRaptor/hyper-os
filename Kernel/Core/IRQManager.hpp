#pragma once

#include <LibC/stdint.h>

class IRQManager
{
private:
	static IRQManager m_Instance;

public:
	void RegisterBasicInterrupts();

	static IRQManager& Get();
	
private:
	void RegisterInterruptRequest(size_t index, unsigned long address);
};