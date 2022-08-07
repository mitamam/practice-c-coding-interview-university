#include <stdio.h>
#include <stdlib.h>

char *copy_string(char *src, int n)
{
	char *dst;
	
	if (src == NULL || n <= 0)
		return NULL;
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (dst == NULL)
		return NULL;
	for (int i = 0; src[i] != '\0'; i++)
		dst[i] = src[i];
	dst[n] = '\0';
	return (dst);
}

int main(void)
{
	char *s;

	s = copy_string("cat", 3);
	if (s == NULL)
		return 1;
	for (int i = 0; *(s + i) != '\0'; i++)
		printf("%c", *(s + i));
	printf("\n");
	free(s);
	return 0;
}