#-------------------------------------------------------------------------------------------
# Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------------------
# AK
#-------------------------------------------------------------------------------------------
set(SOURCES
	Bitmap.cpp
	IoService.cpp
	Logger.cpp
	Serial.cpp
	Spinlock.cpp
	String.cpp)

set(HEADERS
	Array.hpp
	Assertion.hpp
	Bitmap.hpp
	IoService.hpp
	Iterator.hpp
	Logger.hpp
	Math.hpp
	Memory.hpp
	Serial.hpp
	Spinlock.hpp
	String.hpp
	StringView.hpp
	TypeTraits.hpp
	Utility.hpp
	Vector.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Wnull-dereference")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -fno-pic -fno-rtti -ffreestanding -fbuiltin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables -fno-stack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-80387 -mno-mmx -mno-sse -mno-sse2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=kernel -mno-red-zone")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_library(AK STATIC ${SOURCES} ${HEADERS})
target_include_directories(AK PUBLIC src/)
