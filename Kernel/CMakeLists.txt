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
# Kernel
#-------------------------------------------------------------------------------------------
set(KERNEL_SOURCES
        src/Kernel/main.cpp
        src/Kernel/Common/CxxAbi.cpp
        src/Kernel/Common/IoService.cpp
        src/Kernel/Common/Logger.cpp
        src/Kernel/Common/Memory.cpp
        src/Kernel/Common/MMIO.cpp
        src/Kernel/Common/Serial.cpp
        src/Kernel/Common/String.cpp
        src/Kernel/Memory/Bitmap.cpp
        src/Kernel/Memory/KernelMemory.cpp
        src/Kernel/Memory/PhysicalMemoryManager.cpp
        src/Kernel/Memory/VirtualMemoryManager.cpp
        src/Kernel/Synchronization/Spinlock.cpp
        src/Kernel/System/ACPI.cpp
        src/Kernel/System/APIC.cpp
        src/Kernel/System/CPU.cpp
        src/Kernel/System/IDT.cpp
        src/Kernel/System/GDT.cpp
        src/Kernel/System/MADT.cpp
        src/Kernel/System/PIC.cpp
        src/Kernel/System/SMP.cpp)

set(KERNEL_HEADERS
        include/Kernel/main.hpp
        include/Kernel/Common/CxxAbi.hpp
        include/Kernel/Common/IoService.hpp
        include/Kernel/Common/Logger.hpp
        include/Kernel/Common/Math.hpp
        include/Kernel/Common/Memory.hpp
        include/Kernel/Common/MMIO.hpp
        include/Kernel/Common/Registers.hpp
        include/Kernel/Common/Optional.hpp
        include/Kernel/Common/Serial.hpp
        include/Kernel/Common/String.hpp
        include/Kernel/Common/Utility.hpp
        include/Kernel/Common/Vector.hpp
        include/Kernel/Memory/Bitmap.hpp
        include/Kernel/Memory/KernelMemory.hpp
        include/Kernel/Memory/PhysicalMemoryManager.hpp
        include/Kernel/Memory/VirtualMemoryManager.hpp
        include/Kernel/Synchronization/Spinlock.hpp
        include/Kernel/System/ACPI.hpp
        include/Kernel/System/APIC.hpp
        include/Kernel/System/CPU.hpp
        include/Kernel/System/IDT.hpp
        include/Kernel/System/GDT.hpp
        include/Kernel/System/MADT.hpp
        include/Kernel/System/PIC.hpp
        include/Kernel/System/SMP.hpp)

if ("${ARCH}" STREQUAL "x86_64")
    set(ARCH_SOURCES
            src/Kernel/Arch/x86_64/Stivale.cpp
            src/Kernel/Arch/x86_64/Interrupts.asm)

    set(ARCH_HEADERS
            include/Kernel/Arch/x86_64/Stivale.hpp)
elseif ("${ARCH}" STREQUAL "x86_32")
    # TODO: Implement x86_32
endif ()

set(SOURCES
        ${KERNEL_SOURCES}
        ${ARCH_SOURCES})

set(HEADERS
        ${KERNEL_HEADERS}
        ${ARCH_HEADERS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -fno-pic -fno-rtti -fno-exceptions -ffreestanding -fbuiltin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables -fno-stack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-80387 -mno-mmx -mno-sse -mno-sse2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=kernel -mno-red-zone")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/src/Kernel/Arch/${ARCH}/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ffreestanding -static -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-pie -fno-pic -nodefaultlibs -nostartfiles")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z max-page-size=0x1000")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

add_executable(kernel ${SOURCES} ${HEADERS} ${ASM_SOURCES})
add_dependencies(kernel echfs limine stivale)
target_link_libraries(kernel PRIVATE limine stivale)
target_include_directories(kernel PRIVATE include)

#-------------------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------------------
install(TARGETS kernel DESTINATION ${CMAKE_BINARY_DIR}/Root/boot)
install(FILES src/Kernel/Arch/${ARCH}/limine.cfg DESTINATION ${CMAKE_BINARY_DIR}/Root/boot)
