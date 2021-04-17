cmake_minimum_required(VERSION 3.16)

project(HyperOS)

#enable_language(C ASM_NASM)
enable_language(C ASM-ATT)

set(CMAKE_C_STANDARD 11)

set(ARCH "elf")
set(TARGET "x86_64")
set(TOOLS "$ENV{HOME}/../../mnt/c/Users/Leon/Desktop/opt")
set(CMAKE_C_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-gcc")
set(CMAKE_LINKER "${TOOLS}/bin/${TARGET}-${ARCH}-gcc")
set(CMAKE_ASM_COMPILER "${TOOLS}/bin/${TARGET}-${ARCH}-as")

add_subdirectory(ThirdParty)

add_subdirectory(Kernel)
add_subdirectory(Userland)