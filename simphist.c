#include "simpshell.h"

char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renum_hist(info_t *info);

/**
 * get_hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *info)
{
	char *buff, *dir;

	dir = simp_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) *
			(simp_strlen(dir) + simp _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	simp_strcpy(buff, dir);
	simp_strcat(buff, "/");
	simp_strcat(buf, HIST_FILE);
	return (buff);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filenamme = get_hist_file(info);
	list_t *node = NULL;

	if (!filenamme)
		return (-1);

	fd = open(filenamme, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenamme);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		simp_putsfd(node->str, fd);
		simp_putfd('\n', fd);
	}
	simp_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *info)
{
	int z, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filenamme = get_hist_file(info);

	if (!filenamme)
		return (0);

	fd = open(filenamme, O_RDONLY);
	free(filenamme);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (z = 0; z < fsize; z++)
		if (buff[z] == '\n')
		{
			buff[z] = 0;
			build_hist_list(info, buff + last, linecount++);
			last = z + 1;
		}
	if (last != z)
		build_hist_list(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_nod_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int z = 0;

	while (node)
	{
		node->num = z++;
		node = node->next;
	}
	return (info->histcount = z);
}
