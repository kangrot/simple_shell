#include "simpshell.h"

/**
 **simp_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *simp_memset(char *s, char b, unsigned int n)
{
	unsigned int z;

	for (z = 0; z < n; z++)
		s[z] = b;
	return (s);
}

/**
 * simp_ffree - frees a string of strings
 * @pp: string of strings
 */
void simp_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * simp_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_si: byte size of previous block
 * @new_si: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *simp_realloc(void *ptr, unsigned int old_si, unsigned int new_si)
{
	char *p;

	if (!ptr)
		return (malloc(new_si));
	if (!new_si)
		return (free(ptr), NULL);
	if (new_si == old_si)
		return (ptr);

	p = malloc(new_si);
	if (!p)
		return (NULL);

	old_si = old_si < new_si ? old_si : new_si;
	while (old_si--)
		p[old_si] = ((char *)ptr)[old_si];
	free(ptr);
	return (p);
}
