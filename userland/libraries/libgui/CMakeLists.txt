cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE LIBGUI_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE LIBGUI_C_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(SOURCES "${LIBGUI_C_SOURCES}" "${LIBGUI_C_HEADERS}")

add_library(libgui STATIC "${SOURCES}")
set_target_properties(libgui PROPERTIES LINKER_LANGUAGE C)
set_target_properties(libgui PROPERTIES OUTPUT_NAME libgui)
