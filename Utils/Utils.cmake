#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

function(hyperos_add_library target)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -fno-pie -fno-pic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -nostdinc -nostdinc++ -nodefaultlibs -nostartfiles")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-pie -fno-pic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib -nostdinc -nostdinc++ -nodefaultlibs -nostartfiles")

    add_library(${target} STATIC ${SOURCES} ${HEADERS})
    target_include_directories(${target} PUBLIC include)
endfunction()