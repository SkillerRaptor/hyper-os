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
set(KERNEL_HDD ${CMAKE_BINARY_DIR}/Root/boot/kernel.hdd)
set(ECHFS_COMMAND ${CMAKE_SOURCE_DIR}/ThirdParty/echfs/echfs-utils)
set(LIMINE_INSTALL_COMMAND ${CMAKE_SOURCE_DIR}/ThirdParty/limine/limine-install-linux-${ARCH})
set(LIMINE_SYS_PATH ${CMAKE_SOURCE_DIR}/ThirdParty/limine/limine.sys)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Base/ DESTINATION ${CMAKE_BINARY_DIR}/Root)
install(TARGETS kernel DESTINATION ${CMAKE_BINARY_DIR}/Root/boot)
install(FILES src/Kernel/Arch/${ARCH}/limine.cfg DESTINATION ${CMAKE_BINARY_DIR}/Root/boot)

install(CODE "execute_process(COMMAND bash -c \"rm -f ${KERNEL_HDD}\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"dd if=/dev/zero bs=1M count=0 seek=64 of=${KERNEL_HDD}\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"parted -s ${KERNEL_HDD} mklabel msdos\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"parted -s ${KERNEL_HDD} mkpart primary 1 100%\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"${ECHFS_COMMAND} -m -p0 ${KERNEL_HDD} quick-format 32768\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"${ECHFS_COMMAND} -m -p0 ${KERNEL_HDD} import ${CMAKE_BINARY_DIR}/Root/boot/kernel kernel\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"${ECHFS_COMMAND} -m -p0 ${KERNEL_HDD} import ${CMAKE_BINARY_DIR}/Root/boot/limine.cfg limine.cfg\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"${ECHFS_COMMAND} -m -p0 ${KERNEL_HDD} import ${LIMINE_SYS_PATH} limine.sys\" OUTPUT_QUIET ERROR_QUIET)")
install(CODE "execute_process(COMMAND bash -c \"${LIMINE_INSTALL_COMMAND} ${KERNEL_HDD}\" OUTPUT_QUIET ERROR_QUIET)")
