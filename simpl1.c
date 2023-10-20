#include "simpshell.h"

/**
 * add_nod - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nod(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	simp_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = simp_strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_nod_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nod_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *nod;

	if (!head)
		return (NULL);

	nod = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	simp_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = simp_strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_stri - prints only the str element of a list_t linked list
 * @q: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_stri(const list_t *q)
{
	size_t z = 0;

	while (q)
	{
		_puts(q->str ? q->str : "(nil)");
		_puts("\n");
		q = q->next;
		z++;
	}
	return (z);
}

/**
 * delete_nod_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nod_at_index(list_t **head, unsigned int index)
{
	list_t *nod, *prev_nod;
	unsigned int z = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nod = *head;
		*head = (*head)->next;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *head;
	while (nod)
	{
		if (z == index)
		{
			prev_nod->next = nod->next;
			free(nod->str);
			free(nod);
			return (1);
		}
		z++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nod, *next_nod, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*head_ptr = NULL;
}
