#ifndef HYPEROS_KERNEL_SYSTEM_PIT_H_
#define HYPEROS_KERNEL_SYSTEM_PIT_H_

#include <stdint.h>

#define PIT_MAX_FREQUENCY 1193180
#define PIT_DATA_PORT 0x40

#define PIT_CHANNEL_0 (0x0)
#define PIT_CHANNEL_1 (1 << 6)
#define PIT_CHANNEL_2 (1 << 7)
#define PIT_LOW_AND_HIGH_BYTE (1 << 5 | 1 << 4)
#define PIT_SQUARE_WAVE_GENERATOR (1 << 2 | 1 << 1)

void pit_init(uint32_t frequency);
void pit_handle_tick(void);
uint64_t pit_get_ticks(void);

#endif //HYPEROS_KERNEL_SYSTEM_PIT_H_
