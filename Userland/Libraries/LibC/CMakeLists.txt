cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE "SOURCE" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib -fpic")

add_library(LibC SHARED ${SOURCE})