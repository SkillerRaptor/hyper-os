#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Kernel
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp)

set(HEADERS
        )

add_executable(Kernel ${SOURCES} ${HEADERS})
target_include_directories(
        Kernel
        PRIVATE
        include)
target_link_libraries(
        Kernel
        PRIVATE
        ProjectOptions
        ProjectWarnings
        stivale)
target_compile_options(
        Kernel
        PRIVATE
        -ffreestanding
        -fno-stack-protector
        -fno-omit-frame-pointer
        -fno-pic
        -fno-strict-aliasing
        -mcmodel=kernel
        -mno-80387
        -mno-mmx
        -mno-3dnow
        -mno-sse
        -mno-sse2
        -mno-red-zone)
target_link_options(
        Kernel
        PRIVATE
        -T ${CMAKE_CURRENT_SOURCE_DIR}/src/Boot/linker.ld
        -nostdlib
        -no-pie
        -static
        -z max-page-size=0x1000)

add_custom_command(
        TARGET Kernel
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${LIMINE_PATH}/limine-cd.bin ${CMAKE_SOURCE_DIR}/Boot
        COMMAND ${CMAKE_COMMAND} -E copy ${LIMINE_PATH}/limine-eltorito-efi.bin ${CMAKE_SOURCE_DIR}/Boot
        COMMAND ${CMAKE_COMMAND} -E copy ${LIMINE_PATH}/limine.sys ${CMAKE_SOURCE_DIR}/Boot
        COMMAND ${CMAKE_COMMAND} -E copy ${LIMINE_PATH}/limine-install-linux-x86_64 ${CMAKE_SOURCE_DIR}/Boot
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Boot/limine.cfg ${CMAKE_SOURCE_DIR}/Boot
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Kernel> ${CMAKE_SOURCE_DIR}/Boot
        COMMAND /bin/sh ${CMAKE_SOURCE_DIR}/Source/Scripts/Build_Image.sh)
