cmake_minimum_required(VERSION 3.10)

project(HyperOS)

enable_language(ASM-ATT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(ARCH "elf")
set(TARGET "x86_64")
set(TOOLS "$ENV{HOME}/opt/cross")
set(CMAKE_ASM_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-as")
set(CMAKE_C_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-gcc")
set(CMAKE_LINKER "${TOOLS}/bin/${TARGET}-${ARCH}-ld")

add_subdirectory(thirdparty)

add_subdirectory(kernel)
#add_subdirectory(userland)