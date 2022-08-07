#include <stdio.h>

int **pascaltriangle(int n)
{
	int pt[n][n];

	for (int i = 0; i < n; i++)
	{
		pt[i][0] = 1;
		for (int j = 1; j < i; j++)
			pt[i][j] = pt[i - 1][j - 1] + pt[i - 1][j];
		pt[i][i] = 1;
	}
	return pt;
}

int main(void)
{
	int n;
	int **pt;

	n = 10;
	pt = pascaltriangle(n);
	for (int i = 0; i < n; i++)
		printf("%d\n", pt[i]);
}