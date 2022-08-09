cmake_minimum_required(VERSION 3.24)

set(This Vector)

project(${This} C CXX)

# specify the C and C++ standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

# add_library(${This} STATIC vector.c vector.h)
add_library(${This} vector.c vector.h)

add_subdirectory(test)