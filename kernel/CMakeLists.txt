#-------------------------------------------------------------------------------------------
# Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Kernel
#-------------------------------------------------------------------------------------------
set(SOURCES
		src/main.c
		src/arch/acpi.c
		src/arch/apic.c
		src/arch/boot.c
		src/arch/cpu.c
		src/arch/gdt.c
		src/arch/idt.c
		src/arch/interrupts.asm
		src/arch/io.c
		src/arch/madt.c
		src/arch/pic.c
		src/lib/assert.c
		src/lib/logger.c
		src/lib/memory.c
		src/lib/string.c
		src/memory/bitmap.c
		src/memory/kmalloc.c
		src/memory/pmm.c
		src/memory/vmm.c)

set(HEADERS
		include/arch/acpi.h
		include/arch/apic.h
		include/arch/boot.h
		include/arch/cpu.h
		include/arch/gdt.h
		include/arch/idt.h
		include/arch/io.h
		include/arch/madt.h
		include/arch/pic.h
		include/lib/assert.h
		include/lib/logger.h
		include/lib/math.h
		include/lib/memory.h
		include/lib/string.h
		include/memory/bitmap.h
		include/memory/kmalloc.h
		include/memory/pmm.h
		include/memory/vmm.h)

add_executable(kernel ${SOURCES} ${HEADERS})
target_include_directories(kernel PRIVATE include)
target_link_libraries(kernel PRIVATE limine)
target_compile_options(kernel PRIVATE
		-O0
		-fno-stack-check
		-fno-stack-protector
		-fno-asynchronous-unwind-tables
		-fno-pic
		-fno-pie
		-ffreestanding
		-nostdlib
		-mabi=sysv
		-mno-80387
		-mno-mmx
		-mno-3dnow
		-mno-sse
		-mno-sse2
		-mno-ssse3
		-mno-sse4
		-mno-sse4a
		-mno-sse4.1
		-mno-sse4.2
		-mno-avx
		-mno-avx2
		-mno-avx512f
		-mno-red-zone
		-msoft-float
		-mcmodel=kernel)

target_link_options(kernel PRIVATE
		-T${CMAKE_CURRENT_SOURCE_DIR}/boot/linker.ld
		-nostdlib
		--no-pie
		-melf_x86_64
		-zmax-page-size=0x1000
		-static)

#-------------------------------------------------------------------------------------------
# Iso
#-------------------------------------------------------------------------------------------
add_custom_command(OUTPUT HyperOS.iso DEPENDS kernel
		COMMAND make -C ${CMAKE_SOURCE_DIR}/third_party/limine
		COMMAND mkdir -p ${CMAKE_BINARY_DIR}/boot
		COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/kernel ${CMAKE_CURRENT_SOURCE_DIR}/boot/limine.cfg ${CMAKE_SOURCE_DIR}/third_party/limine/limine.sys ${CMAKE_SOURCE_DIR}/third_party/limine/limine-cd.bin ${CMAKE_SOURCE_DIR}/third_party/limine/limine-cd-efi.bin ${CMAKE_BINARY_DIR}/boot
		COMMAND xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label ${CMAKE_BINARY_DIR}/boot -o ${CMAKE_BINARY_DIR}/HyperOS.iso
		COMMAND ${CMAKE_SOURCE_DIR}/third_party/limine/limine-deploy ${CMAKE_BINARY_DIR}/HyperOS.iso
)

add_custom_target(iso ALL DEPENDS HyperOS.iso)

#-------------------------------------------------------------------------------------------
# Run
#-------------------------------------------------------------------------------------------
add_custom_target(run DEPENDS HyperOS.iso COMMAND qemu-system-x86_64 -M q35 -m 2G -cdrom ${CMAKE_BINARY_DIR}/HyperOS.iso)
