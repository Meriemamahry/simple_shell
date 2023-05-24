#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
int leng = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
leng++;
ret = malloc(sizeof(char) * (leng + 1));
if (!ret)
return (NULL);
for (leng++; leng--;)
ret[leng] = *--str;
return (ret);
}

/**
 *_puts - prints input str
 *@str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * _putchar - c to stdout
 * @c: character to print
 * Return: 1 o -1
 */
int _putchar(char c)
{
static int j;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
write(1, buf, j);
j = 0;
}
if (c != BUF_FLUSH)
buf[j++] = c;
return (1);
}
