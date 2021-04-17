#include "pit.h"

#include "io_service.h"
#include "pic.h"

#include <utilities/logger.h>

#define PIT_IRQ_MASK 0x0

#define PIT_MAX_FREQUENCY 1193180

#define PIT_COMMAND_PORT 0x43
#define PIT_CHANNEL_0_DATA_PORT 0x40

#define PIT_LOW_AND_HIGH_BYTE (1 << 5 | 1 << 4)
#define PIT_SQUARE_WAVE_GENERATOR (1 << 2 | 1 << 1)

static uint64_t ticks = 0;

void pit_init(uint32_t frequency)
{
	info("Initializing PIT...");
	
	pic_clear_interrupt_request_mask(PIT_IRQ_MASK);
	
	uint32_t divisor = PIT_MAX_FREQUENCY / frequency;
	
	uint8_t low_byte = (uint8_t) (divisor & 0xFF);
	uint8_t high_byte = (uint8_t) ((divisor >> 8) & 0xFF);
	
	io_outb(PIT_COMMAND_PORT, PIT_LOW_AND_HIGH_BYTE | PIT_SQUARE_WAVE_GENERATOR);
	io_outb(PIT_CHANNEL_0_DATA_PORT, low_byte);
	io_outb(PIT_CHANNEL_0_DATA_PORT, high_byte);
	info(" The frequency was set to %dhz!", frequency);
	
	info("Initializing PIT finished!");
}

void pit_handle_tick(void)
{
	ticks++;
}

uint64_t pit_get_ticks(void)
{
	return ticks;
}