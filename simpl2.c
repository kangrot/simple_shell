#include "simpshell.h"

/**
 * list_leng - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_leng(const list_t *h)
{
	size_t z = 0;

	while (h)
	{
		h = h->next;
		z++;
	}
	return (z);
}

/**
 * list_to_stri - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_stri(list_t *head)
{
	list_t *node = head;
	size_t z = list_leng(head), j;
	char **strs;
	char *str;

	if (!head || !z)
		return (NULL);
	strs = malloc(sizeof(char *) * (z + 1));
	if (!strs)
		return (NULL);
	for (z = 0; node; node = node->next, z++)
	{
		str = malloc(simp_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < z; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = simp_strcpy(str, node->str);
		strs[z] = str;
	}
	strs[z] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t z = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		z++;
	}
	return (z);
}

/**
 * node_starts - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_nod_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nod_index(list_t *head, list_t *node)
{
	size_t z = 0;

	while (head)
	{
		if (head == node)
			return (z);
		head = head->next;
		z++;
	}
	return (-1);
}
