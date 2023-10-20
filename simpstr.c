#include "simpshell.h"

/**
 * simp_strlen - returns the length of a string
 * @a: the string whose length to check
 *
 * Return: integer length of string
 */
int simp_strlen(char *a)
{
	int z = 0;

	if (!a)
		return (0);

	while (*a++)
		z++;
	return (z);
}

/**
 * simp_strcmp - performs lexicogarphic comparison of two strangs.
 * @a1: the first strang
 * @a2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int simp_strcmp(char *a1, char *a2)
{
	while (*a1 && *a2)
	{
		if (*a1 != *a2)
			return (*a1 - *a2);
		a1++;
		a2++;
	}
	if (*a1 == *a2)
		return (0);
	else
		return (*a1 < *a2 ? -1 : 1);
}

/**
 * starts - checks if needle starts with haystack
 * @kanstack: string to search
 * @pin: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts(const char *kanstack, const char *pin)
{
	while (*pin)
		if (*pin++ != *kanstack++)
			return (NULL);
	return ((char *)kanstack);
}

/**
 * simp_strcat - concatenates two strings
 * @dk: the destination buffer
 * @srcc: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *simp_strcat(char *dk, char *srcc)
{
	char *rett = dk;

	while (*dk)
		dk++;
	while (*srcc)
		*dk++ = *srcc++;
	*dk = *srcc;
	return (rett);
}
