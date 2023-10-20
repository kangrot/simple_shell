#include "simpshell.h"

/**
 * simp_strcpy - copies a string
 * @dk: the destination
 * @srcc: the source
 *
 * Return: pointer to destination
 */
char *simp_strcpy(char *dk, char *srcc)
{
	int z = 0;

	if (dk == srcc || srcc == 0)
		return (dk);
	while (srcc[z])
	{
		dk[z] = srcc[z];
		z++;
	}
	dk[z] = 0;
	return (dk);
}

/**
 * simp_strdup - duplicates a string
 * @stri: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *simp_strdup(const char *stri)
{
	int lent = 0;
	char *retu;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		lent++;
	retu = malloc(sizeof(char) * (lent + 1));
	if (!retu)
		return (NULL);
	for (lent++; lent--;)
		retu[lent] = *--stri;
	return (retu);
}

/**
 *_puts - prints an input string
 *@stri: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *stri)
{
	int z = 0;

	if (!stri)
		return;
	while (stri[z] != '\0')
	{
		_putchar(stri[z]);
		z++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @w: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char w)
{
	static int z;
	static char buff[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(1, buff, z);
		z = 0;
	}
	if (w != BUF_FLUSH)
		buff[z++] = w;
	return (1);
}
