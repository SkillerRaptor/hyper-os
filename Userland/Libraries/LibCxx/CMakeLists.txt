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
        src/libcxx.cpp)

set(HEADERS
        include/array
        include/cassert
        include/cstddef
        include/iterator
        include/type_traits)

add_library(libcxx STATIC ${SOURCES} ${HEADERS})
target_include_directories(libcxx INTERFACE include)
