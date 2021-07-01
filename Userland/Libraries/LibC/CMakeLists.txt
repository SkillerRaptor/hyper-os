#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------------------
# LibCxx
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/LibC.c
        src/setjmp.c
        src/signal.c
        src/stdio.c
        src/stdlib.c
        src/string.c)

set(HEADERS
        include/assert.h
        include/setjmp.h
        include/signal.h
        include/stdarg.h
        include/stddef.h
        include/stdint.h
        include/stdio.h
        include/stdlib.h
        include/string.h
        include/time.h
        include/uchar.h
        include/sys/cdefs.h
        include/sys/types.h)

hyperos_add_library(LibC)