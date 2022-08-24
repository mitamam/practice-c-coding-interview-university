#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

int binary_search(const int *arr, const int key, const int n);
int binary_search_rec(const int *arr, const int key,
	 int min,  int max);

#endif