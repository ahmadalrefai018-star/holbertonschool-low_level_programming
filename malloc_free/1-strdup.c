#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * containing a copy of the string given as a parameter
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if it fails
 */
char *_strdup(char *str)
{
	unsigned int len = 0, i;
	char *copy;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	copy = malloc((len + 1) * sizeof(char));

	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = str[i];

	return (copy);
}
