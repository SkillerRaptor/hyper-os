/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

void logger_init();

void logger_info(const char *format, ...);
void logger_warning(const char *format, ...);
void logger_error(const char *format, ...);
void logger_debug(const char *format, ...);
