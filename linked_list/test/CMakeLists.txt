cmake_minimum_required(VERSION 3.24)

set(This LinkedListTest)

add_executable(${This} test.cpp)
target_link_libraries(${This} PUBLIC
	gtest_main
	LinkedList
)

add_test(
	NAME ${This}
	COMMAND ${This}
)