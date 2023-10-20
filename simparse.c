#include "simpshell.h"

int simp_is_cmd(info_t *info, char *path);
char *simp_dup_chars(char *pathstr, int start, int stop);
char *simp_find_path(info_t *info, char *pathstr, char *cmd);

/**
 * simp_is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int simp_is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * simp_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *simp_dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int z = 0, h = 0;

	for (h = 0, z = start; z < stop; z++)
		if (pathstr[z] != ':')
			buff[h++] = pathstr[z];
	buff[h] = 0;
	return (buff);
}

/**
 * simp_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *simp_find_path(info_t *info, char *pathstr, char *cmd)
{
	int z = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((simp_strlen(cmd) > 2) && starts(cmd, "./"))
	{
		if (simp_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[z] || pathstr[z] == ':')
		{
			path = simp_dup_chars(pathstr, curr_pos, z);
			if (!*path)
				simp_strcat(path, cmd);
			else
			{
				simp_strcat(path, "/");
				simp_strcat(path, cmd);
			}
			if (simp_is_cmd(info, path))
				return (path);
			if (!pathstr[z])
				break;
			curr_pos = z;
		}
		z++;
	}
	return (NULL);
}
