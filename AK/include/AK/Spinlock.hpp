#pragma once

#include <stdint.h>

namespace AK
{
	class Spinlock
	{
	public:
		void lock();
		void unlock();
	
	private:
		volatile uint32_t m_lock;
	};
}
