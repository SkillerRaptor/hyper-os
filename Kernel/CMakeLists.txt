cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE ASM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.asm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -fno-pic -fno-rtti -fno-exceptions -ffreestanding -fbuiltin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables -fno-stack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-80387 -mno-mmx -mno-sse -mno-sse2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=kernel -mno-red-zone")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ./linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ffreestanding -static -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-pie -fno-pic -nodefaultlibs -nostartfiles")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z max-page-size=0x1000")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

add_executable(Kernel.elf ${SOURCES} ${HEADERS} ${ASM_SOURCES})
add_dependencies(Kernel.elf echfs limine stivale)
target_link_libraries(Kernel.elf PRIVATE AK)
target_include_directories(Kernel.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/ThirdParty/stivale)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/limine.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
        TARGET Kernel.elf
        POST_BUILD
        COMMAND /bin/sh ${CMAKE_SOURCE_DIR}/Scripts/Build-HDD.sh
)
