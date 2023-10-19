#include "simpshell.h"

/**
 **simp_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *simp_strncpy(char *dest, char *src, int n)
{
	int z, j;
	char *s = dest;

	i = 0;
	while (src[z] != '\0' && z < n - 1)
	{
		dest[z] = src[z];
		z++;
	}
	if (z < n)
	{
		j = z;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **simp_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *simp_strncat(char *dest, char *src, int n)
{
	int z, j;
	char *s = dest;

	z = 0;
	j = 0;
	while (dest[z] != '\0')
		z++;
	while (src[j] != '\0' && j < n)
	{
		dest[z] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[z] = '\0';
	return (s);
}

/**
 **simp_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *simp_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
