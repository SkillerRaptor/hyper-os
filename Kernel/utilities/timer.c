#include "timer.h"

#include <system/pit.h>

void timer_start(struct timer* timer)
{
	timer->start = pit_get_ticks();
}

uint64_t timer_end(struct timer* timer)
{
	timer->end = pit_get_ticks();
	return timer->end - timer->start;
}