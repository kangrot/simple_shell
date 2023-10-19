#include "simshell.h"
/**
 * find_com - Check if the command exists in the PATH directories
 * @cmmd: The command to check
 * Return: path to the executable if it exists
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
			return (strdup_func(cmmd));
	}
	else
	{
		if (dir == NULL)
			return (NULL);
		cmmd_size = strlen_sim(cmmd);
		dir_clone = strdup_func(dir);
		tokk = strtok(dir_clone, ":");

		while (tokk != NULL)
		{
			dir_size = strlen_sim(tokk);

			if (dir_size + 1 + cmmd_size >= sizeof(fulldir))
			{
				free(dir_clone);
				return (NULL);
			}
			strcpy_sim(fulldir, tokk);
			strcat_sim(fulldir, "/");
			strcat_sim(fulldir, cmmd);
			if (access(fulldir, F_OK) == 0)
			{
				free(dir_clone);
				return (strdup_func(fulldir));
			}
			tokk = strtok(NULL, ":");
		}
		free(dir_clone);
	}
	return (NULL);
}
