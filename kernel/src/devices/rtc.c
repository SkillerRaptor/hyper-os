/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "devices/rtc.h"

#include "arch/fadt.h"
#include "arch/io.h"
#include "lib/logger.h"

#include <stdbool.h>

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

static uint8_t s_century_register = 0;

static bool rtc_is_updating(void);
static uint8_t rtc_read_register(uint8_t rtc_register);

void rtc_init(void)
{
	s_century_register = fadt_get_century();
	logger_info("RTC: Initialized");
}

uint8_t rtc_get_second(void)
{
	const uint8_t seconds = rtc_read_register(0x00);
	const uint8_t second = (seconds & 0x0f) + ((seconds / 16) * 10);
	return second;
}

uint8_t rtc_get_minute(void)
{
	const uint8_t minutes = rtc_read_register(0x02);
	const uint8_t minute = (minutes & 0x0f) + ((minutes / 16) * 10);
	return minute;
}

uint8_t rtc_get_hour(void)
{
	const uint8_t hours = rtc_read_register(0x04);
	const uint8_t hour =
		((hours & 0x0f) + (((hours & 0x70) / 16) * 10)) | (hours & 0x80);
	return hour;
}

uint8_t rtc_get_day(void)
{
	const uint8_t days = rtc_read_register(0x07);
	const uint8_t day = (days & 0x0f) + ((days / 16) * 10);
	return day;
}

uint8_t rtc_get_month(void)
{
	const uint8_t months = rtc_read_register(0x08);
	const uint8_t month = (months & 0x0f) + ((months / 16) * 10);
	return month;
}

uint16_t rtc_get_year(void)
{
	const uint8_t years = rtc_read_register(0x09);
	const uint8_t year = (years & 0x0f) + ((years / 16) * 10);
	return year + rtc_get_century() * 100;
}

uint8_t rtc_get_century(void)
{
	const uint8_t centuries = rtc_read_register(s_century_register);
	const uint8_t century = (centuries & 0x0f) + ((centuries / 16) * 10);
	return century;
}

struct time rtc_get_time(void)
{
	struct time time = { 0 };
	time.second = rtc_get_second();
	time.minute = rtc_get_minute();
	time.hour = rtc_get_hour();

	return time;
}

struct date rtc_get_date(void)
{
	struct date date = { 0 };
	date.day = rtc_get_day();
	date.month = rtc_get_month();
	date.year = rtc_get_year();
	date.century = rtc_get_century();

	return date;
}

static bool rtc_is_updating(void)
{
	io_out8(CMOS_ADDRESS, 0x0a);
	return (io_in8(CMOS_DATA) & 0x80);
}

static uint8_t rtc_read_register(uint8_t rtc_register)
{
	while (rtc_is_updating())
	{
		// NOTE: Prevents compiler from optimizing loop
		__asm__ __volatile__("");
	}

	io_out8(CMOS_ADDRESS, rtc_register);
	return io_in8(CMOS_DATA);
}
