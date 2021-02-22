cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_STATIC}")

file(GLOB_RECURSE "KERNEL_SOURCE" "${CMAKE_SOURCE_DIR}/*.c")
file(GLOB_RECURSE "ASM_SOURCE" "${CMAKE_SOURCE_DIR}/*.s")

set("SOURCE" ${KERNEL_SOURCE} ${ASM_SOURCE})

add_compile_options(-mcmodel=kernel)
add_link_options(-mcmodel=kernel)

add_link_options(LINKER:-T ${CMAKE_CURRENT_BINARY_DIR}/linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000)

file(GENERATE OUTPUT linker.ld INPUT linker.ld)

add_executable(Kernel ${SOURCE})