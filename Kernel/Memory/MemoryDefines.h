#pragma once

#include <stdint.h>
#include <stddef.h>

static constexpr uint64_t KERNEL_BASE_ADDRESS = 0xFFFFFFFF80000000;
static constexpr uint64_t PHYSICAL_MEMORY_OFFSET = 0xFFFF800000000000;
static constexpr size_t PAGE_SIZE = 4096;
static constexpr size_t BYTE_SIZE = 8;