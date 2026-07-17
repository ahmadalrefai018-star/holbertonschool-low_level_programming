#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: string
 *
 * Return: pointer to str
 */
char *cap_string(char *str)
{
	int i = 0;
	int j;
	char sep[] = " \t\n,;.!?\"(){}";

	while (str[i] != '\0')
	{
		if (i == 0 && str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;

		j = 0;
		while (sep[j] != '\0')
		{
			if (str[i] == sep[j] &&
			    str[i + 1] >= 'a' &&
			    str[i + 1] <= 'z')
			{
				str[i + 1] -= 32;
			}
			j++;
		}
		i++;
	}

	return (str);
}
