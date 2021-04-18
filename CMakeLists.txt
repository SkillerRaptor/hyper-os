cmake_minimum_required(VERSION 3.10)

project(HyperOS)

enable_language(ASM-ATT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS ON)

set(ARCH "elf")
set(TARGET "x86_64")
set(TOOLS "$ENV{HOME}/opt/cross")
set(TOOLS "$ENV{HOME}/../../mnt/c/Users/Leon/Desktop/opt")
set(CMAKE_C_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-gcc")
set(CMAKE_LINKER "${TOOLS}/bin/${TARGET}-${ARCH}-gcc")
set(CMAKE_ASM_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-as")

add_subdirectory(ThirdParty)

add_subdirectory(kernel)
add_subdirectory(userland)