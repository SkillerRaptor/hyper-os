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
set(CMAKE_CXX_STANDARD 20)

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

add_library(LibCpp STATIC ${SOURCES} ${HEADERS})
target_include_directories(LibCpp PUBLIC include)
