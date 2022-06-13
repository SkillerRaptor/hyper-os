/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/acpi.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/string.h"
#include "memory/pmm.h"

#include <stdbool.h>

struct rsdp
{
	char signature[8];
	uint8_t checksum;
	char oem_id[6];
	uint8_t revision;
	uint32_t rsdt_address;

	uint32_t length;
	uint64_t xsdt_address;
	uint8_t extended_checksum;
	uint8_t reserved[3];
} __attribute__((packed));

struct rsdt
{
	struct sdt header;
	char list[];
} __attribute__((packed));

static bool s_is_xsdt = false;
static struct rsdt *s_rsdt = NULL;

static struct sdt *acpi_get_sdt(size_t index)
{
	if (s_is_xsdt)
	{
		const uint64_t *ptr = (uint64_t *) s_rsdt->list;
		assert(ptr != NULL);

		return (struct sdt *) (ptr[index] + pmm_get_memory_offset());
	}

	const uint32_t *ptr = (uint32_t *) s_rsdt->list;
	assert(ptr != NULL);

	return (struct sdt *) (ptr[index] + pmm_get_memory_offset());
}

void acpi_init(void)
{
	struct limine_rsdp_response *rsdp_response = boot_get_rsdp();
	assert(rsdp_response != NULL);

	struct rsdp *rsdp = (struct rsdp *) rsdp_response->address;
	assert(rsdp != NULL);

	s_is_xsdt = rsdp->revision == 2 && rsdp->xsdt_address != 0;

	const uint64_t address = s_is_xsdt ? rsdp->xsdt_address : rsdp->rsdt_address;
	s_rsdt = (struct rsdt *) (address + pmm_get_memory_offset());
	assert(s_rsdt != NULL);

	logger_info(
		"ACPI: Found %s at 0x%016x",
		s_is_xsdt ? "XSDT" : "RSDT",
		(uintptr_t) s_rsdt);

	logger_info("ACPI: Initialized");
}

void *acpi_find_sdt(const char *signature, size_t index)
{
	assert(signature != NULL);

	size_t count = 0;
	const size_t entries = s_rsdt->header.length - sizeof(struct sdt);
	for (size_t i = 0; i < entries / 4; ++i)
	{
		struct sdt *sdt = acpi_get_sdt(i);
		assert(sdt != NULL);

		if (!strncmp(sdt->signature, signature, 4) && (count++ == index))
		{
			return (void *) sdt;
		}
	}

	return NULL;
}
