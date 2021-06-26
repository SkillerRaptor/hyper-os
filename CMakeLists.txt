#-------------------------------------------------------------------------------------------
# Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(HyperOS LANGUAGES ASM_NASM C CXX)

#-------------------------------------------------------------------------------------------
# CXX Standard
#-------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#-------------------------------------------------------------------------------------------
# Toolchain
#-------------------------------------------------------------------------------------------
set(TOOLCHAIN_PREFIX ${CMAKE_SOURCE_DIR}/Toolchain/CrossCompiler/Tools/${ARCH}/bin)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}/${ARCH}-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}/${ARCH}-elf-g++)
set(CMAKE_LINKER_COMPILER ${TOOLCHAIN_PREFIX}/${ARCH}-elf-ld)
set(CMAKE_AS_COMPILER ${TOOLCHAIN_PREFIX}/${ARCH}-elf-as)
set(CMAKE_AR_COMPILER ${TOOLCHAIN_PREFIX}/${ARCH}-elf-ar)
set(CMAKE_ASM_COMPILER nasm)

#-------------------------------------------------------------------------------------------
# ThirdParty
#-------------------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

#-------------------------------------------------------------------------------------------
# Warning Flags
#-------------------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-address-of-packed-member")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-expansion-to-defined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wimplicit-fallthrough")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmisleading-indentation")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonnull-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wundef")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")

include_directories(.)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/AK)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Kernel)
