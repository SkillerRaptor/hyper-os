cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE KERNEL_SOURCES "${CMAKE_SOURCE_DIR}/Kernel/*.c")
file(GLOB_RECURSE KERNEL_HEADERS "${CMAKE_SOURCE_DIR}/Kernel/*.h")
file(GLOB_RECURSE KERNEL_ASM_SOURCES "${CMAKE_SOURCE_DIR}/Kernel/*.asm")

set(CMAKE_C_FLAGS "-ffreestanding -fno-builtin -nostdlib -fno-stack-protector -mcmodel=kernel")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wundef -Wcast-qual -Wwrite-strings -Werror")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/Kernel/linker.ld -ffreestanding -static -nostdlib -no-pie -mcmodel=kernel -nodefaultlibs -nostartfiles -z max-page-size=0x1000")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

add_executable(Kernel.elf ${KERNEL_SOURCES} ${KERNEL_HEADERS} ${KERNEL_ASM_SOURCES})
add_dependencies(Kernel.elf echfs limine)
target_include_directories(Kernel.elf PRIVATE ${CMAKE_SOURCE_DIR}/Kernel/)
target_link_libraries(Kernel.elf gcc)

#file(COPY "${CMAKE_SOURCE_DIR}/limine.cfg" DESTINATION "${CMAKE_BINARY_DIR}/Kernel")

add_custom_command(
        TARGET Kernel.elf
        COMMAND ${CMAKE_COMMAND} -E env THIRD_PARTY_HOME=${CMAKE_SOURCE_DIR}/ThirdParty
        /bin/sh "${CMAKE_SOURCE_DIR}/Scripts/Build.sh")