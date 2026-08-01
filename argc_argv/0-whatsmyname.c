#include <stdio.h>

/**
 * main - prints the name of the program
 * @argc: the number of arguments passed to the program
 * @argv: array of arguments passed to the program
 *
 * Return: always 0 (Success)
 */
int main(int argc, char *argv[])
{
	(void)argc;

	printf("%s\n", argv[0]);

	return (0);
}
