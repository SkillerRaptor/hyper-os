cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_STATIC}")

file(GLOB_RECURSE "SOURCE" "${CMAKE_SOURCE_DIR}/*.c")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-warning-option")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE -fno-rtti -ffreestanding -fbuiltin")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-80387 -mno-mmx -mno-sse -mno-sse2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-stack-protector")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
add_compile_options(-mcmodel=kernel)
add_link_options(-mcmodel=kernel)

add_link_options(LINKER:-T ${CMAKE_CURRENT_BINARY_DIR}/linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000)

file(GENERATE OUTPUT linker.ld INPUT linker.ld)

add_executable(Kernel ${SOURCE})
#target_link_libraries(Kernel LibC LibAK)
