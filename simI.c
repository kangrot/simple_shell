#include "simshell.h"
/**
  * read_incom - Uses getline to read input of user and handles EOF condition
  * Return: the input string
  */

char *read_incom()
{
	char *linebuff = NULL;
	size_t len = 0;
	ssize_t line_len;

	if (isatty(STDIN_FILENO) == 1)
	{
		write(STDOUT_FILENO, "~$ ", 3);
	}

	line_len = getline(&linebuff, &len, stdin);

	if (line_len == -1)
	{
		free(linebuff);
		write(STDOUT_FILENO, "\n", 2);
		return (NULL);
	}
	/* prompt on newline if user taps on only enter, or spaces */
	if (linebuff[0] == '\n' || (strspn_alt(linebuff, " \t\r\n") ==
				strlen_alt(linebuff)))
	{
		free(linebuff);
		return (read_incom()); /*calling function recursively*/
	}

	if (linebuff[strlen_alt(linebuff) - 1] != '\n')
	{
		len += 2;
		linebuff = (char *)realloc(linebuff, len);
		if (linebuff == NULL)
		{
			free(linebuff);
			perror("No allocated space");
			return (NULL);
		}
		linebuff[strlen_alt(linebuff) - 1] = '\0';
	}

	return (linebuff);
}
