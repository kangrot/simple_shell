#include "simshell.h"
/**
 * simshell_strtok - separates string into tokens with a delimiter
 * @str: string to be used
 * @delim: delimiter
 * Return: tokenized string
 */
char *simshell_strtok(char *str, const char *delim)
{
	char *_token;
	static char *_rem;

	if (str != NULL)
	{
		_rem = str;
	}

	if (_rem == NULL || *_rem == '\0')
	{
		return (NULL);
	}

	while (*_rem != '\0' && strchr_alt(delim, *_rem) != NULL)
	{
		_rem++;
	}

	if (*_rem == '\0')
	{
		return (NULL);
	}

	_token = _rem;
	while (*_rem != '\0' && strchr(delim, *_rem) == NULL)
	{
		_rem++;
	}
	if (*_rem != '\0')
	{
		*_rem = '\0';
		_rem++;
	}
	return (_token);
}
