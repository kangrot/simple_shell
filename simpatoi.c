#include "simpshell.h"

int simp_interactive(info_t *info);
int simp_is_delim(char c, char *delim);
int simp_isalpha(int c);
int simp_atoi(char *s);

/**
 * simp_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int simp_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * simp_is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int simp_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *simp_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int simp_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *simp_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int simp_atoi(char *s)
{
	int z, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (z = 0;  s[z] != '\0' && flag != 2; z++)
	{
		if (s[z] == '-')
			sign *= -1;

		if (s[z] >= '0' && s[z] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[z] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
