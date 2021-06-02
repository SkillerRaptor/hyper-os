cmake_minimum_required(VERSION 3.10)

add_custom_target(
        echfs
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/echfs
)

add_custom_target(
        limine
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/limine
)

add_custom_target(
        stivale
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stivale
)
