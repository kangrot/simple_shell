#include "simphell.h"

/**
 * simp_clear_info - initializes info_t struct
 * @info: struct address
 */
void simp_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * simp_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void simp_set_info(info_t *info, char **av)
{
	int z = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = simp_strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = simp_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (z = 0; info->argv && info->argv[z]; z++)
			;
		info->argc = z;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * simp_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void simp_free_info(info_t *info, int all)
{
	simp_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmmd_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		simp_ffree(info->environ);
			info->environ = NULL;
		simp_bfree((void **)info->cmmd_buff);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
