#include "variadic_functions.h"

/**
 * print_char - prints a char from a va_list
 * @ap: the va_list containing the value
 *
 * Return: void
 */
void print_char(va_list ap)
{
	printf("%c", va_arg(ap, int));
}

/**
 * print_int - prints an int from a va_list
 * @ap: the va_list containing the value
 *
 * Return: void
 */
void print_int(va_list ap)
{
	printf("%d", va_arg(ap, int));
}

/**
 * print_float - prints a float from a va_list
 * @ap: the va_list containing the value
 *
 * Return: void
 */
void print_float(va_list ap)
{
	printf("%f", va_arg(ap, double));
}

/**
 * print_string - prints a string from a va_list, or (nil) if NULL
 * @ap: the va_list containing the value
 *
 * Return: void
 */
void print_string(va_list ap)
{
	char *str;
	char *options[2];

	str = va_arg(ap, char *);
	options[0] = str;
	options[1] = "(nil)";
	printf("%s", options[str == NULL]);
}

/**
 * print_all - prints anything, based on a format string
 * @format: list of types of arguments passed to the function
 *
 * Return: void
 */
void print_all(const char * const format, ...)
{
	fmt_t table[] = {
		{"c", print_char},
		{"i", print_int},
		{"f", print_float},
		{"s", print_string},
		{NULL, NULL}
	};
	va_list ap;
	unsigned int i, j, printed;

	i = 0;
	printed = 0;
	va_start(ap, format);
	while (format && format[i])
	{
		j = 0;
		while (table[j].type != NULL)
		{
			if (table[j].type[0] == format[i])
			{
				if (printed)
					printf(", ");
				table[j].f(ap);
				printed = 1;
			}
			j++;
		}
		i++;
	}
	va_end(ap);
	printf("\n");
}
