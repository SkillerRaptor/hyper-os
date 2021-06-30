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
        include/cstddef
        include/iterator
        include/type_traits)

add_library(LibCpp STATIC ${SOURCES} ${HEADERS})
target_include_directories(LibCpp INTERFACE include)
