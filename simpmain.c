#include "simpshell.h"

/**
 * main - entry point
 * @ad: arg count
 * @ax: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ad, char **ax)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ad == 2)
	{
		fd = open(ax[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				simp_eputs(ax[0]);
				simp_eputs(": 0: Can't open ");
				simp_eputs(ax[1]);
				simp_eputchar('\n');
				simp_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_env_list(info);
	read_hist(info);
	hsh(info, ax);
	return (EXIT_SUCCESS);
}
