#include "simpshell.h"

/**
 * simp_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int simp_myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * simp_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int simp_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int retu;

	p = simp_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	retu = delete_nod_at_index(&(info->alias),
		get_nod_index(info->alias, nod_starts(info->alias, str, -1)));
	*p = c;
	return (retu);
}

/**
 * simp_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int simp_set_alias(info_t *info, char *str)
{
	char *p;

	p = simp_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (simp_unset_alias(info, str));

	simp_unset_alias(info, str);
	return (add_nod_end(&(info->alias), str, 0) == NULL);
}

/**
 * simp_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int simp_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = simp_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * simp_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int simp_myalias(info_t *info)
{
	int z = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			simp_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (z = 1; info->argv[z]; z++)
	{
		p = simp_strchr(info->argv[z], '=');
		if (p)
			simp_set_alias(info, info->argv[z]);
		else
			simp_print_alias(nod_starts(info->alias, info->argv[z], '='));
	}

	return (0);
}
