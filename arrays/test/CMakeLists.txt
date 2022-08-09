cmake_minimum_required(VERSION 3.24)

set(This VectorTest)

add_executable(${This} vector_test.cpp)
target_link_libraries(${This} PUBLIC
	gtest_main
	Vector
)

add_test(
	NAME ${This}
	COMMAND ${This}
)