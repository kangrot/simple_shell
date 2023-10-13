#include "simshell.h"

/**
  * simshell_loop - Loops shell and implements functions
  * until ctrl + d is entered
  * @argc: number of command line arguments.
  * @argv: array of command lie arguments.
  * Return: void
  */
void simshell_loop(int argc, char **argv)
{
	int crite = 1;
	char *linebuff = NULL;
	char **tokk_made;

	do {
		linebuff = read_incom(argc, argv);
		if (linebuff == NULL)
		{
			free(linebuff);
			break;
		}
		tokk_made = tok_input(linebuff);

		crite = exec_com(tokk_made);

		free(linebuff);
		free_tok(tokk_made);

	} while (crite);
}

/**
  * main - runs a simple unix command line interpreter
  * @argc: number of command line arguments
  * @argv: an array of command line arguments
  * Return: the value of the last executed command
  */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	int stat = 0;

	simshell_loop(argc, argv);

	return (stat);
}

/**
  * free_tok - frees memory allocated for each token generated
  * @tokk_made: double pointer to array of tokens
  */

void free_tok(char **tokk_made)
{
	int z;

	if (tokk_made == NULL)
	{
		return;
	}

	for (z = 0; tokk_made[z] != NULL; z++)
	{
		free(tokk_made[z]);
	}
	free(tokk_made);
}
