#include "shell.h"

/**
 *ptu - prints string
 * @s: a string
 */
void ptu(char *s)
{
int i = 0;

if (!s)
return;
while (s[i] != '\0')
{
ptu_char(s[i]);
i++;
}
}

/**
 * ptu_char - writes
 * @c: The character
 * Return: 1
 */
int _eputchar(char c)
{
static char buf[WRITE_BUF_SIZE];
static int k;

if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
{
write(2, buf, k);
k = 0;
}
if (c != BUF_FLUSH)
buf[k++] = c;
return (1);
}

/**
 * _fdt - writing
 * @c: a char
 * @i: a filedescriptor
 * Return: 1
 */
int _fdt(char c, int i)
{
static char buf[WRITE_BUF_SIZE];
static int j;

if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
write(i, buf, j);
j = 0;
}
if (c != BUF_FLUSH)
buf[j++] = c;
return (1);
}

/**
 *_fds- prints...
 * @s: a string
 * @i: a filedescriptor
 * Return: number
 */
int _fds(char *s, int i)
{
int j = 0;

if (!s)
return (0);
while (*s)
{
j += _fdt(*s++, i);
}
return (j);
}
