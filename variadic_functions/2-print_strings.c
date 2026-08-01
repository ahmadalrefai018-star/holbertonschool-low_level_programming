#include "variadic_functions.h"

/**
 * print_strings - prints strings separated by a separator
 * @separator: string printed between two strings
 * @n: the number of parameters
 *
 * Return: void
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i;
	char *str;

	va_start(ap, n);
	for (i = 0; i < n; i++)
	{
		if (i > 0 && separator != NULL)
			printf("%s", separator);

		str = va_arg(ap, char *);
		if (str == NULL)
			printf("(nil)");
		else
			printf("%s", str);
	}
	va_end(ap);
	printf("\n");
}
