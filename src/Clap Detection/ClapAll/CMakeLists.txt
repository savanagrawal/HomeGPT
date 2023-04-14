cmake_minimum_required(VERSION 3.1.0)

project(FIRdemo)

set (CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable (second second.cpp)
target_link_libraries(second fir_static)
target_include_directories(second PRIVATE ..)

