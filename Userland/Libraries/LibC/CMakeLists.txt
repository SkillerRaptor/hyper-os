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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -fno-pie -fno-pic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -nostdinc -nodefaultlibs -nostartfiles")

add_library(LibC STATIC ${SOURCES} ${HEADERS})
target_include_directories(LibC PUBLIC include)