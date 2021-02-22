#ifndef HYPEROS_INTERRUPTS_PIC_H_
#define HYPEROS_INTERRUPTS_PIC_H_

#include <stdint.h>

#define MASTER_COMMAND_SELECTOR 0x20
#define MASTER_DATA_SELECTOR 0x21

#define SLAVE_COMMAND_SELECTOR 0xA0
#define SLAVE_DATA_SELECTOR 0xA1

void pic_remap(uint8_t master_offset, uint8_t slave_offset);
void pic_disable(void);

void pic_send_end_of_interrupt(uint8_t interrupt_request_line);

void pic_set_interrupt_request_mask(uint8_t interrupt_request_line);
void pic_clear_interrupt_request_mask(uint8_t interrupt_request_line);

uint16_t pic_get_in_service_register(void);
uint16_t pic_get_interrupt_request_register(void);

#endif
