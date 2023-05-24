#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _eputs(char *str1)
{
int k = 0;

if (!str1)
return;
while (str1[k] != '\0')
{
_eputchar(str1[k]);
k++;
}
}

/**
 * _eputchar - writes
 * @c: The character
 * Return: 1
 */
int _eputchar(char c)
{
static int k;
static char buf[WRITE_BUF_SIZE];

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
 * _putfd - writes
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: 1
 */
int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 *_putsfd - prints an
 * @str: the string
 * @fd: the filedescriptor to write to
 * Return: the number
 */
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _putfd(*str++, fd);
}
return (i);
}
