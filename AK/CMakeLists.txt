cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE "SOURCE" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library(LibAK SHARED ${SOURCE})