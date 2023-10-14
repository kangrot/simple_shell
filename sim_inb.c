#include "simshell.h"

/**
 * exit_simshell - handles the exit command.
 *
 * Desc: 'this function is responsible
 *for exiting the shell'
 *@stat:represents integer value to specicify the exit status
 * Return:void
 *
 **/

void exit_simshell(int stat)
{
	exit(stat);
}



/**
 * control_b_com - a function that matches or checks for a builtin function
 * @tokk_made: pointer to user input tokenized for execution
 */
void control_b_com(char **tokk_made)
{
	if (strcmp_sim(tokk_made[0], "exit") == 0)
	{
		int stat = 0;

		if (tokk_made[1] != NULL)

		{
			stat = atoi_sim(tokk_made[1]);
		}

		exit_simshell(stat);
	}

	else if (strcmp_sim(tokk_made[0], "env") == 0)
	{
		/* shell_env();*/

		return;
	}
}
