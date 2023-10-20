#include "simpshell.h"

/**
 * simp_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *simp_strcpy(char *dest, char *src)
{
	int z = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[z])
	{
		dest[z] = src[i];
		z++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * simp_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *simp_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_putchar(str[z]);
		z++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(1, buf, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buf[z++] = c;
	return (1);
}
