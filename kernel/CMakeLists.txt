cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE KERNEL_ASM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.asm")
file(GLOB_RECURSE KERNEL_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE KERNEL_C_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(KERNEL_STANDARD_FLAGS "-ffreestanding -fno-builtin -nostdlib -fno-stack-protector -mcmodel=kernel")
set(KERNEL_OPTIMIZATION_FLAGS "-O2")
set(KERNEL_WARNING_FLAGS "-Wall -Wextra -Wundef -Wcast-qual -Wwrite-strings -Werror")

set(CMAKE_C_FLAGS "${KERNEL_STANDARD_FLAGS} ${KERNEL_OPTIMIZATION_FLAGS} ${KERNEL_WARNING_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld -ffreestanding -static -nostdlib -no-pie -mcmodel=kernel -nodefaultlibs -nostartfiles -z max-page-size=0x1000")

add_executable(kernel.elf "${KERNEL_C_SOURCES}" "${KERNEL_C_HEADERS}" "${KERNEL_ASM_SOURCES}")
add_dependencies(kernel.elf echfs limine)
target_include_directories(kernel.elf PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(kernel.elf gcc)

add_custom_command(
        TARGET kernel.elf
        COMMAND ${CMAKE_COMMAND} -E env THIRD_PARTY_HOME=${CMAKE_SOURCE_DIR}/thirdparty
        /bin/sh ${CMAKE_SOURCE_DIR}/scripts/build.sh
)

add_custom_command(
        TARGET kernel.elf
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/kernel/build/kernel.hdd ${CMAKE_SOURCE_DIR}/kernel.hdd
)
