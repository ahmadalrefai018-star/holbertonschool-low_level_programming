#include "main.h"

/**
 * sqrt_helper - searches for the natural square root
 * @n: number to check
 * @guess: possible square root
 *
 * Return: natural square root, or -1
 */
int sqrt_helper(int n, int guess)
{
	if (n % guess == 0 && n / guess == guess)
		return (guess);

	if (guess > n / guess)
		return (-1);

	return (sqrt_helper(n, guess + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: number to calculate
 *
 * Return: natural square root, or -1 if it does not exist
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);

	if (n == 0)
		return (0);

	return (sqrt_helper(n, 1));
}
