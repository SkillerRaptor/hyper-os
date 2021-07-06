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
        src/LibCpp.cpp
        src/new.cpp)

set(HEADERS
        include/array
        include/cassert
        include/csetjmp
        include/csignal
        include/cstddef
        include/cstdint
        include/cstdio
        include/cstdlib
        include/cstring
        include/ctime
        include/cuchar
        include/functional
        include/ios
        include/iterator
        include/memory
        include/new
        include/numbers
        include/string
        include/string_view
        include/type_traits
        include/utility
        include/details/char_traits.h
        include/details/stream_types.h)

hyperos_add_library(cpp)
target_link_libraries(cpp PUBLIC c)
