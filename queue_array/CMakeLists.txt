cmake_minimum_required(VERSION 3.24)

set(This CircularQueue)

project(${This} C CXX)

# specify the C and C++ standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

# add_library(${This} STATIC circular_queue.c circular_queue.h)
add_library(${This} circular_queue.c circular_queue.h)

add_subdirectory(test)