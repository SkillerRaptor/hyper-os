cmake_minimum_required(VERSION 3.16)

project("HyperOS")

set(CMAKE_INSTALL_MESSAGE NEVER)
set(CMAKE_TARGET_MESSAGES OFF)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "x86_64-elf-gcc")
set(CMAKE_CXX_COMPILER "x86_64-elf-g++")
set(CMAKE_ASM_COMPILER "nasm")
set(CMAKE_LINKER "x86_64-elf-gcc")
set(CMAKE_AR "x86-64-elf-ar")

add_custom_target("run"
	COMMAND "${CMAKE_SOURCE_DIR}/Scripts/run.sh"
	USES_TERMINAL
)

add_custom_target("debug"
	COMMAND "${CMAKE_SOURCE_DIR}/Scripts/debug.sh"
	USES_TERMINAL
)

add_custom_target("image"
	COMMAND "${CMAKE_SOURCE_DIR}/Scripts/build.sh"
	USES_TERMINAL
)

add_compile_options(-nostdlib -nostdinc -ffreestanding -fno-stack-protector -Wextra -Wall -Wundef -Wcast-qual -Wwrite-strings)
add_compile_options(-fomit-frame-pointer -mno-red-zone -march=x86-64 -mno-sse -mno-sse2)
add_compile_options(-mno-80387 -mno-mmx -mcmodel=kernel -m64 -fno-exceptions -ffunction-sections -fdata-sections -fmerge-all-constants -fno-unroll-loops -falign-functions=1 -fno-pie -fno-pic)
add_compile_options(-Os -fno-asynchronous-unwind-tables)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/Userland")
include_directories("${CMAKE_SOURCE_DIR}/Userland/Libraries/")
include_directories("${CMAKE_SOURCE_DIR}/Userland/Libraries/LibC")

file(GENERATE OUTPUT limine.bin INPUT limine.bin)
file(GENERATE OUTPUT limine.cfg INPUT limine.cfg)

add_subdirectory("${CMAKE_SOURCE_DIR}/Userland")
add_subdirectory("${CMAKE_SOURCE_DIR}/AK")
add_subdirectory("${CMAKE_SOURCE_DIR}/Kernel")
