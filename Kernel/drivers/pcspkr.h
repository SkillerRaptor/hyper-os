#ifndef HYPEROS_KERNEL_DRIVERS_PCSPKR_H_
#define HYPEROS_KERNEL_DRIVERS_PCSPKR_H_

#include <stdint.h>

void pcspkr_init(void);
void pcspkr_set_frequency(uint32_t frequency);

void pcspkr_play(uint32_t frequency);
void pcspkr_stop();
void pcspkr_beep(uint16_t milliseconds);

#endif // HYPEROS_KERNEL_DRIVERS_PCSPKR_H_
