/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_SIGNAL_H_
#define HYPEROS_LIBC_SIGNAL_H_

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

int kill(pid_t pid, int sig);
int signal(int sig, void (*callback)(int));
int raise(int sig);

__END_DECLS

#endif // HYPEROS_LIBC_SIGNAL_H_
