#include "pit.h"

#include "io_service.h"
#include "pic.h"

#include <lib/logger.h>

static uint64_t ticks = 0;

void pit_init(uint32_t frequency)
{
	info("PIT: Initializing...!");
	
	pic_clear_interrupt_request_mask(0x00);
	
	uint32_t divisor = 1193180 / frequency;
	
	io_outb(0x43, 0x36);
	io_outb(0x40, divisor & 0xFF);
	io_outb(0x40, (divisor >> 8) & 0xFF);
	
	info("PIT: Initializing finished!");
}

void pit_handle_tick(void)
{
	ticks++;
}

uint64_t pit_get_ticks(void)
{
	return ticks;
}
