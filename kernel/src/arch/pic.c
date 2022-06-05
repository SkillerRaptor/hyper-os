/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/pic.h"

#include "arch/io.h"
#include "lib/logger.h"

#define MASTER_COMMAND_SELECTOR 0x20
#define MASTER_DATA_SELECTOR 0x21
#define MASTER_OFFSET 0x20

#define SLAVE_COMMAND_SELECTOR 0xA0
#define SLAVE_DATA_SELECTOR 0xA1
#define SLAVE_OFFSET 0x28

#define ICW1_ICW4 (1 << 0)
#define ICW1_INIT (1 << 4)
#define ICW1_8086 (1 << 0)

#define MASTER_IDENTITY 0x04
#define SLAVE_IDENTITY 0x02

void pic_remap(void)
{
	io_out8(MASTER_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);
	io_wait();
	io_out8(SLAVE_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);
	io_wait();

	io_out8(MASTER_DATA_SELECTOR, MASTER_OFFSET);
	io_wait();
	io_out8(SLAVE_DATA_SELECTOR, SLAVE_OFFSET);
	io_wait();

	io_out8(MASTER_DATA_SELECTOR, MASTER_IDENTITY);
	io_wait();
	io_out8(SLAVE_DATA_SELECTOR, SLAVE_IDENTITY);
	io_wait();

	io_out8(MASTER_DATA_SELECTOR, ICW1_8086);
	io_wait();
	io_out8(SLAVE_DATA_SELECTOR, ICW1_8086);
	io_wait();

	logger_info("Remapped PIC");
}
