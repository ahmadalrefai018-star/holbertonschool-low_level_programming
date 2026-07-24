#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * simple_print_buffer - prints buffer in hexa
 * @buffer: the address of memory to print
 * @size: the size of the memory to print
 */
void simple_print_buffer(char *buffer, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
	{
		if (i % 10)
			printf(" ");
		if (!(i % 10) && i)
			printf("\n");
		printf("0x%02x", buffer[i]);
	}
	printf("\n");
}

int main(void)
{
	char *buffer;

	buffer = create_array(98, 'H');

	if (buffer == NULL)
	{
		printf("Failed to allocate memory\n");
		return (1);
	}

	simple_print_buffer(buffer, 98);
	free(buffer);

	return (0);
}
