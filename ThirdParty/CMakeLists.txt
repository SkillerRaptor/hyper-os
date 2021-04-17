cmake_minimum_required(VERSION 3.16)

add_custom_target(
        echfs
        COMMAND make echfs-utils
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/echfs)

add_custom_target(
        limine
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/limine)

add_custom_command(
        TARGET limine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/limine.cfg ${CMAKE_BINARY_DIR}/Kernel/limine.cfg)

add_custom_command(
        TARGET limine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}//ThirdParty/limine/bin/limine.sys ${CMAKE_BINARY_DIR}/Kernel/limine.sys)

#file(COPY "${CMAKE_SOURCE_DIR}/limine.cfg" DESTINATION "${CMAKE_BINARY_DIR}/Kernel")
#file(COPY "${CMAKE_SOURCE_DIR}/ThirdParty/limine/bin/limine.sys" DESTINATION "${CMAKE_BINARY_DIR}/Kernel")
