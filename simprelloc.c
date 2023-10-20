#include "simpshell.h"

/**
 **simp_memset - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@d: the byte to fill *s with
 *@x: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *simp_memset(char *a, char d, unsigned int x)
{
	unsigned int z;

	for (z = 0; z < x; z++)
		a[z] = d;
	return (a);
}

/**
 * simp_ffree - frees a string of strings
 * @qq: string of strings
 */
void simp_ffree(char **qq)
{
	char **a = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
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
