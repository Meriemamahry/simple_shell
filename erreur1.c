#include "shell.h"

/**
 * _errt - string to an int
 * @s: astring
 * Return: 0 if there is no numbers in string
 *        + number otherwise
 *        +-1 on error
 */
int _errt(char *s)
{
	int i = 0;
	unsigned long int j = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			j *= 10;
			j += (s[i] - '0');
			if (j > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (j);
}

/**
 * printerr - prints error message
 * @i: struct
 * @s: string
 * Return: 0 if no numbers in string
 *         +converted number otherwise
 *         +-1 on error
 */
void printerr(info_t *i, char *s)
{
	ptu(i->fname);
	ptu(": ");
	printDec(i->line_count, STDERR_FILENO);
	ptu(": ");
	ptu(i->argv[0]);
	ptu(": ");
	ptu(s);
}

/**
 * printDec - function prints a decimal number
 * @i: int number
 * @f: filedescriptor
 * Return: number
 */
int printDec(int i, int f)
{
	int (*__putchar)(char) = _putchar;
	unsigned int abso;
	unsigned int l;
	int k, c = 0;

	if (f == STDERR_FILENO)
		__putchar = ptu_char;
	if (i < 0)
	{
		abso = -i;
		__putchar('-');
		c++;
	}
	else
		abso = i;
	l = abso;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (abso / k)
		{
			__putchar('0' + l / k);
			c++;
		}
		l %= k;
	}
	__putchar('0' + l);
	c++;

	return (c);
}

/**
 * convnum - convertes
 * @n: int
 * @e: base
 * @f: int flags
 * Return: string
 */
char *convnum(long int n, int e, int f)
{
	static char *a, buffer[50];
	char s = 0;
	char *p;
	unsigned long i = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		s = '-';

	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = a[i % e];
		i /= e;
	} while (i != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remcomt - Replaces # with \0
 * @c: pointer string
 * Return: 0
 */
void remcomt(char *c)
{
	int i;

	for (i = 0; c[i] != '\0'; i++)
		if (c[i] == '#' && (!i || c[i - 1] == ' '))
		{
			c[i] = '\0';
			break;
		}
}
