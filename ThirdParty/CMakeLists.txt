cmake_minimum_required(VERSION 3.16)

add_custom_target(
        echfs
        COMMAND make echfs-utils
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/echfs)

add_custom_target(
        limine
        COMMAND make limine-install
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/limine)