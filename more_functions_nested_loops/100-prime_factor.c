#include <stdio.h>

/**
 * main - prints the largest prime factor
 *
 * Return: Always 0
 */
int main(void)
{
	unsigned long n = 612852475143;
	unsigned long factor = 2;

	while (factor * factor <= n)
	{
		if (n % factor == 0)
			n /= factor;
		else
			factor++;
	}

	printf("%lu\n", n);

	return (0);
}
