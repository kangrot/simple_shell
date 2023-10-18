#include "simshell.h"
/**
 * control_err - uses write system call to print error message when cmd is not
 * found
 * @namme: name of the shell program
 * @cmmd_count: number of command
 * @cmmd: command
 * @erromsg: error message to be printed out
 */
void control_err(const char *namme, int cmmd_count, const char *cmmd,
const char *erromsg)
{
	char cmmd_num[2];
	char newli = '\n';

	output_str(STDERR_FILENO, namme);
	output_str(STDERR_FILENO, ": ");
	convert_str(cmmd_count, cmmd_num);

	output_str(STDERR_FILENO, cmmd_num);
	output_str(STDERR_FILENO, ": ");
	output_str(STDERR_FILENO, cmmd);
	output_str(STDERR_FILENO, ": ");
	output_str(STDERR_FILENO, erromsg);
	write(STDERR_FILENO, &newli, 1);
}

/**
 * output_str - prints a string to a specified file stream using write
 * @desc: file stream to be printed to
 * @str: string
 */
void output_str(int desc, const char *str)
{
	write(desc, str, strlen(str));
}

/**
 * convert_str - converts a string to an integer
 * @numm: number
 * @str: string to be converted
 * Return: converted string
 */
void convert_str(int numm, char *str)
{
	int z = 0;
	int len = 0;
	int for_now = numm;

	while (for_now > 0)
	{
		for_now /= 10;
		len++;
	}

	for (z = len - 1; z >= 0; z--)
	{
		str[z] = '0' + (numm % 10);
		numm /= 10;
	}
	str[len] = '\0';
}
