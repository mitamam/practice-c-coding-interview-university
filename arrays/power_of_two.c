#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int *array;

	array = (int *)malloc(sizeof(int) * 4);
	for (int i = 16; i <= 128; i *= 2)
	{
		*array = i;
		printf("array[i] %d\n", *array);
		array++;
	}
	array -= 4;
	for (int i = 0; i < 4; i++)
		printf("%d\n", array[i]);
	free(array);
}