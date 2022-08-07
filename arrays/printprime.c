/* -------------------------------------------------------------------------- */
/*                            Sieve of Eratosthenes                           */
/* -------------------------------------------------------------------------- */

#include <stdio.h>

typedef enum e_bool { false, true } t_bool;

void printprime(int n)
{
	t_bool prime[n + 1];

	for (int i = 2; i <= n; i++)
		prime[i] = true;
	for (int divisor = 2; (divisor * divisor) <= n; divisor++) // divisor <= √n
	{
		if (prime[divisor])
		{
			for (int i = 2 * divisor; i <= n; i = i + divisor)
				prime[i] = false;
		}
	}
	for (int i = 2; i <= n; i++)
	{
		if (prime[i])
			printf("%d\n", i);
	}
}

int main(void)
{
	printprime(3);
}