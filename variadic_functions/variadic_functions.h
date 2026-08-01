#ifndef VARIADIC_FUNCTIONS_H
#define VARIADIC_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int sum_them_all(const unsigned int n, ...);
void print_numbers(const char *separator, const unsigned int n, ...);
void print_strings(const char *separator, const unsigned int n, ...);
/**
 * struct fmt - structure for format specifiers
 * @c: format character
 * @f: pointer to function
 */
typedef struct fmt
{
	char type;
	void (*f)(va_list ap);
} fmt_t;

void print_all(const char * const format, ...);

#endif /* VARIADIC_FUNCTIONS_H */
