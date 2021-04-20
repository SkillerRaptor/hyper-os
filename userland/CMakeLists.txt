cmake_minimum_required(VERSION 3.10)

set(USERLAND_STANDARD_FLAGS "-ffreestanding -fno-builtin -nostdlib -fno-stack-protector")
set(USERLAND_OPTIMIZATION_FLAGS "-O2")
set(USERLAND_WARNING_FLAGS "-Wall -Wextra -Wundef -Wcast-qual -Wwrite-strings -Werror")

set(CMAKE_C_FLAGS "${USERLAND_STANDARD_FLAGS} ${USERLAND_OPTIMIZATION_FLAGS} ${USERLAND_WARNING_FLAGS}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libraries")

add_subdirectory(applications)
add_subdirectory(games)
add_subdirectory(libraries)