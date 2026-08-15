#include "lists.h"
#include <stdlib.h>

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: pointer to the head of the list
 * @idx: index where the new node should be added
 * @n: value for the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h,
	unsigned int idx, int n)
{
	dlistint_t *current;
	dlistint_t *new;
	unsigned int i;

	if (h == NULL)
		return (NULL);

	if (idx == 0)
		return (add_dnodeint(h, n));

	current = *h;

	for (i = 0; current != NULL && i < idx - 1; i++)
		current = current->next;

	if (current == NULL)
		return (NULL);

	if (current->next == NULL)
		return (add_dnodeint_end(h, n));

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->n = n;
	new->prev = current;
	new->next = current->next;
	current->next->prev = new;
	current->next = new;

	return (new);
}
