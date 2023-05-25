#include "shell.h"
/**
 **cpy - copie
 *@so: a string
 *@st: a string
 *@nb: chars that will be copied
 *Return: string
 */
char *cpy(char *so, char *st, int nb)
{
	int i = 0, j;
	char *c = so;

	while ((st[i] != '\0') && (i < nb - 1))
	{
		so[i] = st[i];
		i++;
	}
	if (i < nb)
	{
		for (j = i; j < nb; j++)
		{
			so[j] = '\0';
		}
	}
	return (c);
}

/**
 **_ncat - concatenate two string
 *@so: a string
 *@st: a string
 *@nb: number chars
 *Return: return the concatenated string
 */
char *_ncat(char *so, char *st, int nb)
{
	int i = 0, j = 0;
	char *c = so;

	while (so[i] != '\0')
		i++;
	while (st[j] != '\0' && j < nb)
	{
		so[i] = st[j];
		i++;
		j++;
	}
	if (j < nb)
		so[i] = '\0';
	return (c);
}

/**
 **str_chr - finds a char
 *@t: a string
 *@i: a char
 *Return: pointer
 */
char *str_chr(char *t, char i)
{
	do {
		if (*t == i)
			return (t);
	} while (*t++ != '\0');

	return (NULL);
}
