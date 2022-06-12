#-------------------------------------------------------------------------------------------
# Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Cmake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15)
project(HyperOS LANGUAGES ASM_NASM C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET x86_64-unknown-elf)
set(CMAKE_C_LINK_EXECUTABLE "ld.lld <OBJECTS> -o <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>")

set(CMAKE_ASM_NASM_COMPILER "nasm")
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS "asm;nasm;S;s")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "nasm <INCLUDES> -g -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

#-------------------------------------------------------------------------------------------
# Third Party
#-------------------------------------------------------------------------------------------
add_subdirectory(third_party)

#-------------------------------------------------------------------------------------------
# Kernel
#-------------------------------------------------------------------------------------------
add_subdirectory(kernel)
