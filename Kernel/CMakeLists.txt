#-------------------------------------------------------------------------------------------
# Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
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
set(SOURCES
	main.cpp
	Boot/Stivale.cpp
	Memory/KernelMemory.cpp
	Memory/PhysicalMemoryManager.cpp
	Memory/VirtualMemoryManager.cpp
	System/ACPI.cpp
	System/APIC.cpp
	System/CPU.cpp
	System/GDT.cpp
	System/HPET.cpp
	System/IDT.cpp
	System/MADT.cpp
	System/PIC.cpp
	System/SMP.cpp
	System/Stdlib.cpp)

set(HEADERS
	Boot/Stivale.hpp
	Memory/KernelMemory.hpp
	Memory/PhysicalMemoryManager.hpp
	Memory/VirtualMemoryManager.hpp
	System/ACPI.hpp
	System/APIC.hpp
	System/CPU.hpp
	System/GDT.hpp
	System/HPET.hpp
	System/IDT.hpp
	System/MADT.hpp
	System/PIC.hpp
	System/SMP.hpp
	System/Stdlib.hpp)

set(ASM_SOURCES
	System/Interrupts.asm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -fno-pic -fno-rtti -fno-exceptions -ffreestanding -fbuiltin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables -fno-stack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-80387 -mno-mmx -mno-sse -mno-sse2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=kernel -mno-red-zone")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/Arch/${ARCH}/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ffreestanding -static -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-pie -fno-pic -nodefaultlibs -nostartfiles")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z max-page-size=0x1000")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arch/${ARCH}/limine.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Arch/${ARCH})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arch/${ARCH}/linker.ld DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Arch/${ARCH})

add_executable(Kernel.elf ${SOURCES} ${HEADERS} ${ASM_SOURCES})
add_dependencies(Kernel.elf echfs)
target_link_libraries(Kernel.elf PRIVATE AK)
target_include_directories(Kernel.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/ThirdParty/stivale)
