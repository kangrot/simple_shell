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

	/* Set up the signal handler for CTRL+ C */
	signal(SIGINT, simsig_hand);

	if (tokk_made[0] == NULL)
		return (1);

	if (strcmp_sim(tokk_made[0], "cd") == 0)
	{
		/* Handle "cd" command as a special case*/
		if (tokk_made[1] == NULL)
		{
			/*Change to the user's home directory if no directory is specified*/
			if (chdir(getenv("HOME")) != 0)
			{
				perror("cd");
			}
		}
		else
		{
			/* Attempt to change the directory to the specified path */
			if (chdir(tokk_made[1]) != 0)
			{
				perror("cd");
			}
		}
		return (0);
	}

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
