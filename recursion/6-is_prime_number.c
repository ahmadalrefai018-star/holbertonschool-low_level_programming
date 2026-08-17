#include "main.h"

/**
 * prime_helper - checks possible divisors recursively
 * @n: number to check
 * @divisor: possible divisor
 *
 * Return: 1 if prime, otherwise 0
 */
int prime_helper(int n, int divisor)
{
	if (divisor > n / divisor)
		return (1);

	if (n % divisor == 0)
		return (0);

	return (prime_helper(n, divisor + 1));
}

/**
 * is_prime_number - checks whether a number is prime
 * @n: number to check
 *
 * Return: 1 if n is prime, otherwise 0
 */
int is_prime_number(int n)
{
	if (n <= 1)
		return (0);

	return (prime_helper(n, 2));
}