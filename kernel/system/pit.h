#ifndef HYPEROS_KERNEL_SYSTEM_PIT_H_
#define HYPEROS_KERNEL_SYSTEM_PIT_H_

#include <stdint.h>

void pit_init(uint32_t frequency);
void pit_handle_tick(void);
uint64_t pit_get_ticks(void);

#endif //HYPEROS_KERNEL_SYSTEM_PIT_H_
