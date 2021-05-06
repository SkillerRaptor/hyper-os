#include "math.h"

uint64_t math_div_roundup(uint64_t a, uint64_t b)
{
    return (a + (b - 1)) / b;
}

uint64_t math_align_up(uint64_t a, uint64_t b)
{
	return math_div_roundup(a, b) * b;
}

uint64_t math_align_down(uint64_t a, uint64_t b)
{
	return (a / b) * b;
}
