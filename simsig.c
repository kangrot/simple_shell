#include "simshell.h"

/**
 * simsig_hand - signals handler CTRL + C
 * @sig: signal integer
 */

void simsig_hand(int sig)
{
	char *prompt = "\nShell$ ";
	
	/* prevents error of unused variables */
	(void)sig;
	write(1, prompt, strlen(prompt));

	/* clears the buffer */
	fflush(stdout);
}
