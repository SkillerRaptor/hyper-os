/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/acpi.h"

#include "arch/boot.h"
#include "lib/logger.h"
#include "lib/string.h"
#include "memory/pmm.h"

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

struct sdt
{
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oem_id[6];
	char oem_table_id[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
};

struct rsdt
{
	struct sdt sdt;
	uint32_t list[];
};

struct xsdt
{
	struct sdt sdt;
	uint64_t list[];
};

static struct rsdt *s_rsdt = NULL;
static struct xsdt *s_xsdt = NULL;

static struct sdt *acpi_get_sdt(size_t index)
{
	if (s_xsdt != NULL)
	{
		uint64_t *ptr = (uint64_t *) s_xsdt->list;
		return (struct sdt *) (ptr[index] + pmm_get_hhdm_offset());
	}

	uint32_t *ptr = (uint32_t *) s_rsdt->list;
	return (struct sdt *) (ptr[index] + pmm_get_hhdm_offset());
}

void acpi_init(void)
{
	struct limine_rsdp_response *rsdp_response = boot_get_rsdp();
	if (rsdp_response == NULL)
	{
		return;
	}

	struct rsdp *rsdp = (struct rsdp *) rsdp_response->address;
	if (rsdp == NULL)
	{
		return;
	}

	if (rsdp->revision == 2 && rsdp->xsdt_address != NULL)
	{
		s_xsdt = (struct xsdt *) (rsdp->xsdt_address + pmm_get_hhdm_offset());
		return;
	}

	s_rsdt = (struct rsdt *) (rsdp->rsdt_address + pmm_get_hhdm_offset());
}

void *acpi_find_sdt(const char *signature, size_t index)
{
	size_t count = 0;
	const size_t entries =
		(s_xsdt == NULL ? s_rsdt->sdt.length : s_xsdt->sdt.length) -
		sizeof(struct sdt);

	for (size_t i = 0; i < entries / 4; ++i)
	{
		struct sdt *sdt = acpi_get_sdt(i);
		if (!strncmp(sdt->signature, signature, 4) && (count == index))
		{
			return (void *) sdt;
		}

		++count;
	}

	return NULL;
}
