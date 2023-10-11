#include "simshell.h"
/**
 * simshell_strtok - separates string into tokens with a delimiter
 * @str: string to be used
 * @delim: delimiter
 * Return: tokenized string
 */
char *simshell_strtok(char *str, const char *delim)
{
	char *tok;
	static char *rem;

	if (str != NULL)
	{
		rem = str;
	}

	if (rem == NULL || *rem == '\0')
	{
		return (NULL);
	}

	while (*rem != '\0' && strchr(delim, *rem) != NULL)
	{
		rem++;
	}

	if (*rem == '\0')
	{
		return (NULL);
	}

	tok = rem;
	while (*rem != '\0' && strchr(delim, *rem) == NULL)
	{
		rem++;
	}
	if (*rem != '\0')
	{
		*rem = '\0';
		rem++;
	}
	return (tok);
}
