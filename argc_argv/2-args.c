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
	int i = 0;

	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return (0);
}
