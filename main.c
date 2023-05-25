#include "shell.h"

/**
 * main - entry point
 * @c:  count
 * @v: vector
 * Return: 0 or 1 on error
 */
int main(int c, char **v)
{
	info_t i[] = { INFO_INIT };
	int d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (d)
		: "r" (d));

	if (c == 2)
	{
		d = open(v[1], O_RDONLY);
		if (d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ptu(v[0]);
				ptu(": 0: Can't open ");
				ptu(v[1]);
				ptu_char('\n');
				ptu_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		i->readfd = d;
	}
	populate_env_list(i);
	readHistory(i);
	hsh(i, v);
	return (EXIT_SUCCESS);
}
