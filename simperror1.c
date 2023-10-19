#include "simpshell.h"

/**
 * simp_erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int simp_erratoi(char *s)
{
	int z = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (z = 0;  s[z] != '\0'; z++)
	{
		if (s[z] >= '0' && s[z] <= '9')
		{
			result *= 10;
			result += (s[z] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printerror - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printerror(info_t *info, char *estr)
{
	simp_eputs(info->fname);
	simp_eputs(": ");
	printd(info->line_count, STDERR_FILENO);
	simp_eputs(": ");
	simp_eputs(info->argv[0]);
	simp_eputs(": ");
	simp_eputs(estr);
}

/**
 * printd - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int z, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = simp_eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (z = 1000000000; z > 1; z /= 10)
	{
		if (_abs_ / z)
		{
			__putchar('0' + current / z);
			count++;
		}
		current %= z;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_com - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void rem_com(char *buff)
{
	int z;

	for (z = 0; buff[z] != '\0'; z++)
		if (buff[z] == '#' && (!z || buff[z - 1] == ' '))
		{
			buff[z] = '\0';
			break;
		}
}
