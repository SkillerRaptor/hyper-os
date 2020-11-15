#pragma once

#include <LibC/stddef.h>

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