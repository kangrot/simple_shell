#include "simshell.h"

size_t strlen_sim(const char *s);
char *strcat_sim(char *dest, const char *src);
int strcmp_sim(char *s1, char *s2);
char *strchr_sim(const char *s, char c);
char *strcpy_sim(char *dest, char *source);
char *get_simshell_env(const char *variable_name);

/**
 *strlen_sim - Entry point
 * Desc - 'function returning length of a string'
 * @s: string to be measured
 *
 * Return: the length of given string 's'
 */
size_t strlen_sim(const char *s)
{
	size_t len = 0;

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * strcat_sim - Entry point
 * Desc - 'a function concantenating two strings'
 * @dest: char string type
 * @src: char string type
 *
 * Return: pointer to the concantenated string
 */
char *strcat_sim(char *dest, const char *src)
{
	int dest_len = 0;
	int z;


	/*Find the length of the destination string*/


	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}


	/*append the first string to the destination string */


	for (z = 0; src[z] != '\0'; z++)
	{
		dest[dest_len + z] = src[z];
	}
	/* add null terminating character to concantenated string */


	dest[dest_len + z] = '\0';


	return (dest);
}




/**
 * strcmp_sim - Entry point
 * Desc - 'a function comparing two strings'
 * @s1: first string to be checked
 * @s2: second string to be checked
 *
 * Return: value less than 0 means s1 is less than s2
 * value equal to 0 meants s1 = s2
 * value greater than 0 means s1 is greater than s2
 */


int strcmp_sim(char *s1, char *s2)
{
	int len;


	for (len = 0; s1[len] == s2[len] && s1[len]; len++)
		;


	if (s1[len] > s2[len])
		return (1);
	if (s1[len] < s2[len])
		return (-1);
	return (0);
}


/**
 * strchr_sim - Entry point
 * Desc - ' a function searching for the first occurence of a character
 * in a string'
 * @s: a pointer to the string to be searched
 * @c: the character to be searched for
 *
 * Return: a pointer to the first occurrence of the char c in s
 * 0R 0 if char c is not found in s
 */


char *strchr_sim(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/**
 * memcpy_sim - Entry point
 * Desc: 'function copying memory area'
 * @src: source char string type
 * @dest: destination string type
 * @n: maximum number of byte area to be copied
 * Return: pointer to destination string
 */


char *memcpy_sim(char *dest, char *src, unsigned int n)
{
	unsigned int z = 0;


	for (z = 0; z < n; z++)
	{
		dest[z] = src[z];


	}
	return (dest);
}
/**
 * strcpy_sim - Entry point
 * Desc - 'a function copying one pointer to another pointer'
 * @source: char type string
 * @dest: char string type
 * Return: Pointer to dest
 */

char *strcpy_sim(char *dest, char *source)
{
	int z = 0;

	while (source[z] != '\0')
	{
		dest[z] = source[z];
		z++;
	}
	dest[z] = '\0';
	return (dest);
}

/**
 * get_simshell_env - Retrieves the value of an environment variable
 * @variable_name: The name of the variable to retrieve
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *get_simshell_env(const char *variable_name)
{
	int name_len = strlen_sim(variable_name);

	char **env;

	for (env = environ; *env; ++env)
	{
		if (strncmp_sim(variable_name, *env, name_len)
				== 0 && (*env)[name_len] == '=')
		{
			return (&((*env)[name_len + 1]));
		}
	}
	return (NULL);
}
