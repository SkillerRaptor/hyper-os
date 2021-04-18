#include "pcspkr.h"

#include <lib/logger.h>
#include <lib/time.h>
#include <system/io_service.h>
#include <system/pit.h>

#define PCSPKR_SOUND_PORT 0x61
#define PCSPKR_COMMAND_PORT 0x42

void pcspkr_init(void)
{
	info("Initializing PC Speaker...");
	
	uint16_t pcspkr_value = io_inb(PCSPKR_SOUND_PORT) | 0x1;
	io_outb(PCSPKR_SOUND_PORT, pcspkr_value);
	
	info("Initializing PC Speaker finished!");
}

void pcspkr_set_frequency(uint32_t frequency)
{
	asm volatile("cli");
	
	uint32_t divisor = PIT_MAX_FREQUENCY / frequency;
	
	uint8_t low_byte = (uint8_t) (divisor & 0xFF);
	uint8_t high_byte = (uint8_t) ((divisor >> 8) & 0xFF);
	
	io_outb(PCSPKR_COMMAND_PORT, PIT_CHANNEL_2 | PIT_LOW_AND_HIGH_BYTE | PIT_SQUARE_WAVE_GENERATOR);
	io_outb(PIT_DATA_PORT, low_byte);
	io_outb(PIT_DATA_PORT, high_byte);
	
	asm volatile("sti");
}

void pcspkr_play(uint32_t frequency)
{
	pcspkr_set_frequency(frequency);
	
	uint8_t temp = io_inb(PCSPKR_SOUND_PORT);
	if (temp != (temp | 3))
	{
		io_outb(PCSPKR_SOUND_PORT, temp | 3);
	}
}

void pcspkr_stop()
{
	uint16_t pcspkr_value = io_inb(PCSPKR_SOUND_PORT) & 0xFC;
	io_outb(PCSPKR_SOUND_PORT, pcspkr_value);
	pcspkr_set_frequency(1);
}

void pcspkr_beep(uint16_t milliseconds)
{
	pcspkr_play(1000);
	time_sleep(milliseconds);
	pcspkr_stop();
}