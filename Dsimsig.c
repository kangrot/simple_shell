#include "simshell.h"

/**
 * ctrl_d_handler - Signal handler for CTRL+D (EOF)
 * @signum: signal integer
 */
void ctrl_d_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
