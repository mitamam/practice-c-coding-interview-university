cmake_minimum_required(VERSION 3.24)

set(This BinarySearchTest)

add_executable(${This} test.cpp)
target_link_libraries(${This} PUBLIC
	gtest_main
	BinarySearch
)

add_test(
	NAME ${This}
	COMMAND ${This}
)