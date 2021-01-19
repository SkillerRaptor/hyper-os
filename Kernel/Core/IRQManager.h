#pragma once

#include <LibC/stddef.h>

class IRQManager
{
private:
	static constexpr const size_t IRQ_BASE_INDEX = 32;

public:
	static void Install();

private:
	void RegisterInterruptRequest(size_t index, uint64_t address);
};