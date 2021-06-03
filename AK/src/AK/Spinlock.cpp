#include <AK/Spinlock.hpp>

namespace AK
{
	void Spinlock::lock()
	{
		while (!__sync_bool_compare_and_swap(&m_lock, 0, 1))
		{
			__builtin_ia32_pause();
		}
	}
	
	void Spinlock::unlock()
	{
		__sync_lock_release(&m_lock);
	}
}
