#include "simpshell.h"

char **simp_strtow(char *stri, char *a);
char **simp_strtow2(char *stri, char a);

/**
 * **simp_strtow - splits a string into words. Repeat delimiters are ignored
 * @stri: the input string
 * @a: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **simp_strtow(char *stri, char *a)
{
	int z, j, k, m, numwords = 0;
	char **s;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!a)
		a = " ";
	for (z = 0; stri[z] != '\0'; z++)
		if (!simp_is_delim(stri[z], a) &&
				(simp_is_delim(stri[z + 1], a) || !stri[z + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, j = 0; j < numwords; j++)
	{
		while (simp_is_delim(stri[z], a))
			z++;
		k = 0;
		while (!simp_is_delim(stri[z + k], a) && stri[z + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = stri[z++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **simp_strtow2 - splits a string into words
 * @stri: the input string
 * @a: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **simp_strtow2(char *stri, char a)
{
	int z, j, k, m, numwords = 0;
	char **s;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (z = 0; stri[z] != '\0'; z++)
		if ((stri[z] != a && stri[z + 1] == a) ||
		    (stri[z] != a && !stri[z + 1]) || stri[z + 1] == a)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, j = 0; j < numwords; j++)
	{
		while (stri[z] == a && stri[z] != a)
			z++;
		k = 0;
		while (stri[z + k] != a && stri[z + k] && stri[z + k] != a)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = stri[z++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
