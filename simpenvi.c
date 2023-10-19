#include "simpshell.h"

/**
 * simp_myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int simp_myenv(info_t *info)
{
	print_list_stri(info->env);
	return (0);
}

/**
 * simp_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *simp_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * simp_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int simp_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		simp_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (simp_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * simp_myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int simp_myunsetenv(info_t *info)
{
	int z;

	if (info->argc == 1)
	{
		simp_eputs("Too few arguements.\n");
		return (1);
	}
	for (z = 1; z <= info->argc; z++)
		simp_unsetenv(info, info->argv[z]);

	return (0);
}

/**
 * pop_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		add_nod_end(&node, environ[z], 0);
	info->env = node;
	return (0);
}
