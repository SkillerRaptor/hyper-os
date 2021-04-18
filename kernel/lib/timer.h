#ifndef HYPEROS_KERNEL_LIB_TIMER_H_
#define HYPEROS_KERNEL_LIB_TIMER_H_

#include <stdint.h>

struct timer
{
	uint64_t start;
	uint64_t end;
};

void timer_start(struct timer* timer);
uint64_t timer_end(struct timer* timer);

#endif // HYPEROS_KERNEL_LIB_TIMER_H_
