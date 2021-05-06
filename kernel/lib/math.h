#ifndef HYPEROS_KERNEL_LIB_MATH_H_
#define HYPEROS_KERNEL_LIB_MATH_H_

#include <stdint.h>

uint64_t math_div_roundup(uint64_t a, uint64_t b);
uint64_t math_align_up(uint64_t a, uint64_t b);
uint64_t math_align_down(uint64_t a, uint64_t b);

#endif // HYPEROS_KERNEL_LIB_MATH_H_
