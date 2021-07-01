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
        src/LibCpp.cpp)

set(HEADERS
        include/array
        include/cassert
        include/csetjmp
        include/csignal
        include/cstddef
        include/cstdint
        include/cstdio
        include/cstring
        include/ctime
        include/cuchar
        include/functional
        include/ios
        include/iterator
        include/numbers
        include/string
        include/string_view
        include/type_traits
        include/utility
        include/details/char_traits.h
        include/details/stream_types.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-pie -fno-pic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib -nostdinc -nostdinc++ -nodefaultlibs -nostartfiles")

add_library(LibCpp STATIC ${SOURCES} ${HEADERS})
target_include_directories(LibCpp PUBLIC include)
target_link_libraries(LibCpp PUBLIC LibC)
