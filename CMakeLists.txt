#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(HyperOS LANGUAGES)

#-------------------------------------------------------------------------------------------
# CXX Standard
#-------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#-------------------------------------------------------------------------------------------
# Toolchain
#-------------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER_FORCED ON)
set(CMAKE_CXX_COMPILER_FORCED ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

set(TOOLCHAIN_PREFIX "${CMAKE_SOURCE_DIR}/Toolchain/CrossCompiler/Tools/bin")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}/x86_64-elf-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}/x86_64-elf-g++")
set(CMAKE_LINKER_COMPILER "${TOOLCHAIN_PREFIX}/x86_64-elf-ld")
set(CMAKE_AS_COMPILER "${TOOLCHAIN_PREFIX}/x86_64-elf-as")
set(CMAKE_AR_COMPILER "${TOOLCHAIN_PREFIX}/x86_64-elf-ar")
set(CMAKE_ASM_COMPILER "nasm")

enable_language(ASM_NASM)
enable_language(C)
enable_language(CXX)

#-------------------------------------------------------------------------------------------
# ThirdParty
#-------------------------------------------------------------------------------------------
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty)

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

#-------------------------------------------------------------------------------------------
# Modules
#-------------------------------------------------------------------------------------------
include(Utils/Utils.cmake)

#-------------------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------------------
install(DIRECTORY Base/ DESTINATION ${CMAKE_BINARY_DIR}/Root)

#-------------------------------------------------------------------------------------------
# Custom Targets
#-------------------------------------------------------------------------------------------
add_custom_target(
        run
        COMMAND ${CMAKE_COMMAND} -E env
        "HYPEROS_BINARY_DIR=${CMAKE_BINARY_DIR}"
        ${CMAKE_SOURCE_DIR}/Meta/Run.sh
        USES_TERMINAL)

add_custom_target(
        debug
        COMMAND ${CMAKE_COMMAND} -E env
        "HYPEROS_BINARY_DIR=${CMAKE_BINARY_DIR}"
        ${CMAKE_SOURCE_DIR}/Meta/Debug.sh
        USES_TERMINAL)

add_custom_target(
        image
        COMMAND ${CMAKE_COMMAND} -E env
        "HYPEROS_SOURCE_DIR=${CMAKE_SOURCE_DIR}"
        "HYPEROS_BINARY_DIR=${CMAKE_BINARY_DIR}"
        ${CMAKE_SOURCE_DIR}/Meta/Build-Image.sh
        USES_TERMINAL)

#-------------------------------------------------------------------------------------------
# Subdirectories
#-------------------------------------------------------------------------------------------
add_subdirectory(Kernel)
add_subdirectory(Userland)
