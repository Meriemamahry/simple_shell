#include "shell.h"

/**
 * f_ree - frees a pointer
 * @p: a pointer
 * Return: 1 if it is free or 0.
 */
int f_ree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
