cmake_minimum_required(VERSION 3.10)
project(HyperOS LANGUAGES ASM_NASM C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TOOLCHAIN_PREFIX /mnt/e/Programme/CrossCompiler/opt/bin)
set(TOOLCHAIN_PREFIX /opt/cross/bin)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}/x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}/x86_64-elf-g++)
set(CMAKE_LINKER_COMPILER ${TOOLCHAIN_PREFIX}/x86_64-elf-gcc)
set(CMAKE_AS_COMPILER ${TOOLCHAIN_PREFIX}/x86_64-elf-as)
set(CMAKE_AR_COMPILER ${TOOLCHAIN_PREFIX}/x86_64-elf-ar)
set(CMAKE_ASM_COMPILER nasm)

if ("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    add_compile_definitions(DEBUG)
endif ()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/AK)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Kernel)
