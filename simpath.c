#include "simshell.h"
/**
 * find_com - Check if the command exists in the PATH directories
 * @cmmd: The command to check
 * Return: path of the executable if it exists
 */
char *find_com(const char *cmmd)
{
	char *dir = getenv("PATH");
	size_t cmmd_size, dir_size;
	char *dir_clone, *tokk;
	char fulldir[1024] = "";

	if (cmmd[0] == '/' || cmmd[0] == '.' || cmmd[0] == '~')
	{
		if (access(cmmd, F_OK) == 0) /*checks existence of command */
			return (strdup(cmmd));
	}
	else
	{
		if (dir == NULL)
			return (NULL);
		cmmd_size = strlen(cmmd);
		dir_clone = strdup(dir);
		tokk = strtok(dir_clone, ":");

		while (tokk != NULL)
		{
			dir_size = strlen(tokk);

			if (dir_size + 1 + cmmd_size >= sizeof(fulldir))
			{
				free(dir_clone);
				return (NULL);
			}
			strcpy(fulldir, tokk);
			strcat(fulldir, "/");
			strcat(fulldir, cmmd);
			if (access(fulldir, F_OK) == 0)
			{
				free(dir_clone);
				return (strdup(fulldir));
			}
			tokk = strtok(NULL, ":");
		}
		free(dir_clone);
	}
	return (NULL);
}
