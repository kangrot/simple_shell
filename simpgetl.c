#include "simpshell.h"

/**
 * simp_input_buf - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t simp_input_buf(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*simp_bfree((void **)info->cmmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, simp_sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = simp_getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_com(*buff);
			build_hist_list(info, *buff, info->histcount++);
			/* if (simp_strchr(*buff, ';')) is this a command chain? */
			{
				*len = r;
				info->cmmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * simp_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t simp_get_input(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t z, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = simp_input_buf(info, &buff, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = z; /* init new iterator to current buf position */
		p = buff + z; /* get pointer for return */

		simp_check_chain(info, buff, &j, z, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (simp_is_chain(info, buff, &j))
				break;
			j++;
		}

		z = j + 1; /* increment past nulled ';'' */
		if (z >= len) /* reached end of buffer? */
		{
			z = len = 0; /* reset position and length */
			info->cmmd_buff_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (simp_strlen(p)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * simp_read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @z: size
 *
 * Return: r
 */
ssize_t simp_read_buf(info_t *info, char *buff, size_t *z)
{
	ssize_t r = 0;

	if (*z)
		return (0);
	r = read(info->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*z = r;
	return (r);
}

/**
 * simp_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int simp_getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t z, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (z == len)
		z = len = 0;

	r = simp_read_buf(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = simp_strchr(buff + z, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = simp_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		simp_strncat(new_p, buff + z, k - z);
	else
		simp_strncpy(new_p, buff + z, k - z + 1);

	s += k - z;
	z = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * simp_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void simp_sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
