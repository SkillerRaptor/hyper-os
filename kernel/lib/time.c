#include "time.h"

#include <system/pit.h>

void time_sleep(uint16_t delay)
{
	uint64_t current_ticks = pit_get_ticks();
	for (;;)
	{
		if (current_ticks + delay < pit_get_ticks())
		{
			break;
		}
	}
}
