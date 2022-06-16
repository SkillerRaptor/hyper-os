/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/fadt.h"

#include "arch/acpi.h"
#include "lib/assert.h"
#include "lib/logger.h"

struct fadt_generic_address
{
	uint8_t address_space;
	uint8_t bit_width;
	uint8_t bit_offset;
	uint8_t access_size;
	uint64_t address;
} __attribute__((packed));

struct fadt_table
{
	struct sdt header;
	uint32_t firmware_control;
	uint32_t dsdt;
	uint8_t reserved_1;
	uint8_t power_management_profile;
	uint16_t sci_interrupt;
	uint32_t smi_command_port;
	uint8_t acpi_enable;
	uint8_t acpi_disable;
	uint8_t s4_bios_request;
	uint8_t p_state_control;
	uint32_t pm1_a_event_block;
	uint32_t pm1_b_event_block;
	uint32_t pm1_a_control_block;
	uint32_t pm1_b_control_block;
	uint32_t pm2_control_block;
	uint32_t pm_timer_block;
	uint32_t gpe0_block;
	uint32_t gpe1_block;
	uint8_t pm_1_event_length;
	uint8_t pm_1_control_length;
	uint8_t pm_2_control_length;
	uint8_t pm_timer_length;
	uint8_t gpe0_length;
	uint8_t gpe1_length;
	uint8_t gpe1_base;
	uint8_t c_state_control;
	uint16_t worst_c2_latency;
	uint16_t worst_c3_latency;
	uint16_t flush_size;
	uint16_t flush_stride;
	uint8_t duty_offset;
	uint8_t duty_width;
	uint8_t day_alarm;
	uint8_t month_alarm;
	uint8_t century;
	uint16_t boot_architecture_flags;
	uint8_t reserved_2;
	uint32_t flags;
	struct fadt_generic_address reset_register;
	uint8_t reset_value;
	uint8_t reserved_3[3];
	uint64_t x_firmware_control;
	uint64_t x_dsdt;
	struct fadt_generic_address x_pm1_a_event_block;
	struct fadt_generic_address x_pm1_b_event_block;
	struct fadt_generic_address x_pm1_a_control_block;
	struct fadt_generic_address x_pm1_b_control_block;
	struct fadt_generic_address x_pm2_Control_block;
	struct fadt_generic_address x_pm_timer_block;
	struct fadt_generic_address x_gpe0_block;
	struct fadt_generic_address x_gpe1_block;
} __attribute__((packed));

static struct fadt_table *s_table = NULL;

void fadt_init(void)
{
	s_table = (struct fadt_table *) acpi_find_sdt("FACP", 0);
	assert(s_table != NULL);

	logger_info("FADT: Initialized");
}
