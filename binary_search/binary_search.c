#include "binary_search.h"

int binary_search(const int *arr, const int key, const int n)
{
	int min, max, mid;

	if (!arr || n <= 0)
		return (-1);
	min = 0;
	max = n - 1;
	while (min <= max)
	{
		mid = min + ((max - min) / 2);
		if (key < arr[mid])
			max = mid - 1;
		else if (key > arr[mid])
			min = mid + 1;
		else
			return (mid);
	}
	return (-1);
}

int binary_search_rec(const int *arr, const int key, int min, int max)
{
	int mid;

	if (!arr || min > max)
		return (-1);
	mid = min + ((max - min) / 2);
	if (key < arr[mid])
		return binary_search_rec(arr, key, min, mid - 1);
	else if (key > arr[mid])
		return binary_search_rec(arr, key, mid + 1, max);
	else
		return (mid);
}