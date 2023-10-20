#include "simpshell.h"

/**
 *simp_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void simp_eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		simp_eputchar(str[z]);
		z++;
	}
}

/**
 * simp_eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int simp_eputchar(char c)
{
	static int z;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buff, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buff[z++] = c;
	return (1);
}

/**
 * simp_putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int simp_putfd(char c, int fd)
{
	static int z;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(fd, buff, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buff[z++] = c;
	return (1);
}

/**
 *simp_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int simp_putsfd(char *str, int fd)
{
	int z = 0;

	if (!str)
		return (0);
	while (*str)
	{
		z += simp_putfd(*str++, fd);
	}
	return (z);
}
