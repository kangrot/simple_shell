#include "simshell.h"
/**
  * tok_input - Uses strtok to form individual tokens from user-input
  * @linebuff: pointer to user input string
  * Return: generated tokens
  */
char **tok_input(char *linebuff)
{
	size_t buff_sim = CMD_LENT, station = 0;
	char **sep_tokspace = malloc(buff_sim * sizeof(char *));
	char *tokk;

	if (linebuff == NULL || sep_tokspace == NULL)
	{
		perror("No allocated space");
		free(sep_tokspace);
		exit(EXIT_FAILURE);
	}

	tokk = strtok(linebuff, TOK_DELI);

	while (tokk != NULL)
	{
		sep_tokspace[station] = strdup_func(tokk);
		if (sep_tokspace[station] == NULL)
		{
			free(sep_tokspace);
			perror("No allocated space");
			exit(EXIT_FAILURE);
		}
		station++;
		if (station >= buff_sim)
		{
			buff_sim += CMD_LENT;
		sep_tokspace = simshell_realloc(
sep_tokspace, buff_sim * sizeof(char *), buff_sim * sizeof(char *));
			if (sep_tokspace == NULL)
			{
				free(sep_tokspace);
				perror("No allocated space");
				exit(EXIT_FAILURE);
			}
		}
		tokk = strtok(NULL, TOK_DELI);
	}
	sep_tokspace[station] = NULL;
	return (sep_tokspace);
}


/**
  * simshell_realloc - reallocates memory
  * @ptr: pointer to new block of memory
  * @old_si: old size
  * @new_si: new size
  * Return: pointer to new memory block if sucessful
  */
void *simshell_realloc(void *ptr, unsigned int old_si, size_t new_si)
{
	char *relo, *clonee;
	unsigned int z;

	if (ptr != NULL)
		clonee = ptr;
	else
	{
		return (malloc(new_si));
	}
	if (new_si == old_si)
		return (ptr);
	if (new_si == 0 && ptr != NULL)
	{
		free(ptr);
		return (0);
	}
	relo = malloc(new_si);
	if (relo == NULL)
		return (NULL);
	for (z = 0; z < old_si && z < new_si; z++)
	{
		*(relo + z) = clonee[z];
	}
	free(ptr);
	return (relo);
}
