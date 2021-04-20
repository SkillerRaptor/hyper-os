cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE TERMINAL_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE TERMINAL_C_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(SOURCES "${TERMINAL_C_SOURCES}" "${TERMINAL_C_HEADERS}")
add_executable(terminal "${SOURCES}")
target_link_libraries(terminal libgui)