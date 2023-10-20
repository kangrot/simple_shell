#include "simpshell.h"

int hsh(info_t *, char **av);
int simp_find_builtin(info_t *info);
void simp_find_cmmd(info_t *info);
void simp_fork_cmmd(info_t *info);

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int simp_builtin_ret = 0;

	while (r != -1 && simp_builtin_ret != -2)
	{
		simp_clear_info(info);
		if (simp_interactive(info))
			_puts("$ ");
		simp_eputchar(BUF_FLUSH);
		r = simp_get_input(info);
		if (r != -1)
		{
			simp_set_info(info, av);
			simp_builtin_ret = simp_find_builtin(info);
			if (simp_builtin_ret == -1)
				simp_find_cmmd(info);
		}
		else if (simp_interactive(info))
			_putchar('\n');
		simp_free_info(info, 0);
	}
	write_hist(info);
	simp_free_info(info, 1);
	if (!simp_interactive(info) && info->status)
		exit(info->status);
	if (simp_builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (simp_builtin_ret);
}

/**
 * simp_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int simp_find_builtin(info_t *info)
{
	int z, built_in_ret = -1;
	simp_builtin_table builtintbl[] = {
		{"exit", simp_myexit},
		{"env", simp_myenv},
		{"help", simp_myhelp},
		{"history", simp_myhistory},
		{"setenv", simp_mysetenv},
		{"unsetenv", simp_myunsetenv},
		{"cd", simp_mycd},
		{"alias", simp_myalias},
		{NULL, NULL}
	};

	for (z = 0; builtintbl[z].type; z++)
		if (simp_strcmp(info->argv[0], builtintbl[z].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[z].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * simp_find_cmmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void simp_find_cmmd(info_t *info)
{
	char *path = NULL;
	int z, h;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (z = 0, h = 0; info->arg[z]; z++)
		if (!simp_is_delim(info->arg[z], " \t\n"))
			h++;
	if (!h)
		return;

	path = simp_find_path(info, simp_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		simp_fork_cmmd(info);
	}
	else
	{
		if ((simp_interactive(info) || simp_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && simp_is_cmd(info, info->argv[0]))
			simp_fork_cmmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerror(info, "not found\n");
		}
	}
}

/**
 * simp_fork_cmmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void simp_fork_cmmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			simp_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerror(info, "Permission denied\n");
		}
	}
}
