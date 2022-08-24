#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../binary_search.h"
}

TEST(BinarySearchTest, BinarySearch)
{
	int arr1[] = {};
	int arr2[] = {1};
	int arr3[] = {10, 20, 40, 60, 70, 80, 110, 120, 140, 190, 200, 210, 230, 270, 300};
	// int arr4[INT_MAX] = {};

	EXPECT_EQ(-1, binary_search(NULL, 10, 5)); // Array is NULL
	EXPECT_EQ(-1, binary_search(arr1, 10, 0)); // Empty array
	EXPECT_EQ(-1, binary_search(arr1, 10, -1)); // Negative n

	EXPECT_EQ(0, binary_search(arr2, 1, 1)); // Only one element(exist)
	EXPECT_EQ(-1, binary_search(arr2, 10, 1)); // Only one element(not exist)

	EXPECT_EQ(0, binary_search(arr3, 10, 15)); // Min
	EXPECT_EQ(7, binary_search(arr3, 120, 15)); // Mid
	EXPECT_EQ(14, binary_search(arr3, 300, 15)); // Max
	EXPECT_EQ(-1, binary_search(arr3, 250, 15)); // Not exist

	// arr4[INT_MAX - 1] = 1;
	// // Check overflow when get the middle index
	// EXPECT_EQ(INT_MAX - 1, binary_search(arr4, 1, INT_MAX));
}

TEST(BinarySearchTest, BinarySearchRecursive)
{
	int arr1[] = {};
	int arr2[] = {1};
	int arr3[] = {10, 20, 40, 60, 70, 80, 110, 120, 140, 190, 200, 210, 230, 270, 300};
	// int arr4[INT_MAX] = {};

	EXPECT_EQ(-1, binary_search_rec(NULL, 10, 0, 9)); // Array is NULL
	EXPECT_EQ(-1, binary_search_rec(arr1, 10, 0, 0)); // Empty array

	EXPECT_EQ(0, binary_search_rec(arr2, 1, 0, 1)); // Only one element(exist)
	EXPECT_EQ(-1, binary_search_rec(arr2, 10, 0, 1)); // Only one element(not exist)

	EXPECT_EQ(0, binary_search_rec(arr3, 10, 0, 14)); // Min
	EXPECT_EQ(7, binary_search_rec(arr3, 120, 0, 14)); // Mid
	EXPECT_EQ(14, binary_search_rec(arr3, 300, 0, 14)); // Max
	EXPECT_EQ(-1, binary_search_rec(arr3, 250, 0, 14)); // Not exist

	// arr4[INT_MAX - 1] = 1;
	// // Check overflow when get the middle index
	// EXPECT_EQ(INT_MAX - 1, binary_search(arr4, 1, INT_MAX));
}