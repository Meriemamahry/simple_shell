#include "shell.h"

/**
 * intera - checks if the shell is in interactive mode
 * @info: list
 * Return: 1 or 0
 */
int intera(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delim - check if i is delimiter
 * @s: char
 * @d: a delimeter
 * Return: 1 or 0
 */
int delim(char s, char *d)
{
while (*d)
	if (*d++ == s)
		return (1);
return (0);
}

/**
 *alpha - check if c is alpha
 *@c: The character to input
 *Return: 1 or 0
 */

int alpha(int c)
{
	if ((c >= 'a' && c <= 'z'))
{
		return (1);
	}
	if ((c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/**
 *toint - convert string to int
 *@k: string to be converted
 *Return: converted number
 */

int toint(char *k)
{
unsigned int l = 0;
int i;
int s = 1, f = 0;

for (i = 0;  k[i] != '\0' && f != 2; i++)
{
if (k[i] == '-')
s *= -1;
if (k[i] >= '0' && k[i] <= '9')
{
f = 1;
l *= 10;
l += (k[i] - '0');
}
else if (f == 1)
f = 2;
}
if (s == -1)
return (-result);
else
return (result);
}
