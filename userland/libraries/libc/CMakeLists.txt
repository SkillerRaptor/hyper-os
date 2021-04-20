cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE LIBC_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE LIBC_C_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(SOURCES "${LIBC_C_SOURCES}" "${LIBC_C_HEADERS}")
add_library(libc STATIC ${SOURCES})
set_target_properties(libc PROPERTIES LINKER_LANGUAGE C)
set_target_properties(libc PROPERTIES OUTPUT_NAME libc)