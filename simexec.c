#include "simshell.h"

int exec_com(char **tokk_made);

/**
 * exec_com - Uses execve and fork to create processes to execute commands
 * @tokk_made: double pointer to commands/tokens
 * Return: 0 if sucessful or bring out an error message for failure
 */
int exec_com(char **tokk_made)
{
	int crite, cmmd_count;
	char *cmmd;
	const char *errocmmd, *namme, *erromsg;
	pid_t ourchild;

	if (tokk_made[0] == NULL)
		return (1);

	control_b_com(tokk_made); /* handle built_ins if presented */
	cmmd = find_com(tokk_made[0]);
	namme = "./hsh", cmmd_count = 1, erromsg = "not found";
	errocmmd = tokk_made[0];
	if (cmmd == NULL)
	{
		free(cmmd);
		int stat = 127;

		control_err(namme, cmmd_count, errocmmd, erromsg);
		return (-1);
	}
	ourchild = fork();
	if (ourchild == -1)
	{perror("child process failed to be created");
		return (1);
	}
	if (!ourchild)
	{
		if (execve(cmmd, tokk_made, environ) == -1)
		{
			perror(cmmd);
			exit(1);
		}
	}
	else
	{
		waitpid(ourchild, &crite, 0);
		int stat;

		if (WIFEXITED(crite))
			stat = WEXITSTATUS(crite);
	}

	free(cmmd);
	return (1);
}
