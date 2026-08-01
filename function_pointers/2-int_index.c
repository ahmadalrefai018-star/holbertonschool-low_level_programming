#include <stddef.h>

/**
 * int_index - searches for the first element in an array for which
 * a comparator function does not return 0
 * @array: the array to search
 * @size: number of elements in the array
 * @cmp: pointer to the function used to compare/test each element
 *
 * Return: the index of the first matching element,
 * or -1 if no element matches or if size <= 0
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
	{
		if (cmp(array[i]))
			return (i);
	}

	return (-1);
}
