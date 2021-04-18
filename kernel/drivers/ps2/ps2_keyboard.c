#include "ps2_keyboard.h"

#include <drivers/qwertz.h>
#include <system/io_service.h>
#include <system/pic.h>
#include <utilities/logger.h>

#define PS2_KEYBOARD_IRQ_MASK 0x1
#define PS2_KEYBOARD_KEY_PORT 0x60

#define KEY_RELEASE_BIT (1 << 7)

void ps2_keyboard_init(void)
{
	info("Initializing PS/2 keyboard...");
	
	pic_clear_interrupt_request_mask(PS2_KEYBOARD_IRQ_MASK);
	info(" IRQ mask was cleared!");
	
	info("Initializing PS/2 keyboard finished!");
}

void ps2_keyboard_handle_action(void)
{
	uint8_t scancode = io_inb(PS2_KEYBOARD_KEY_PORT);
	uint8_t was_released = scancode & KEY_RELEASE_BIT;
	
	uint16_t virtual_key = qwertz_keyboard_map[scancode];
	const char* state = was_released ? "released" : "pressed";
	debug("PS/2 Keyboard: Key was %s! (Scancode: %d | Virtual Key: %d)", state, scancode, virtual_key);
}