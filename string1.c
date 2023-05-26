#include "shell.h"

/**
 * _strcpy - copies a strin
 * @destination: the destination
 * @srce: the source
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *srce)
{
int i = 0;

if (destination == srce || srce == 0)
return (destination);
while (srce[i])
{
destination[i] = srce[i];
i++;
}
destination[i] = 0;
return (destination);
}

/**
 * _strdup - duplicates a string
 * @srce: string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *srce)
{
int leng = 0;
char *ret;

if (srce == NULL)
return (NULL);
while (*srce++)
leng++;
ret = malloc(sizeof(char) * (leng + 1));
if (!ret)
return (NULL);
for (leng++; leng--;)
ret[leng] = *--srce;
return (ret);
}

/**
 *_puts - prints input str
 *@srce: string to be printed
 * Return: Nothing
 */
void _puts(char *srce)
{
int i = 0;

if (!srce)
return;
while (srce[i] != '\0')
{
_putchar(srce[i]);
i++;
}
}

/**
 * _putchar - c to stdout
 * @srce: character to print
 * Return: 1 o -1
 */
int _putchar(char srce)
{
static int j;
static char buf[WRITE_BUF_SIZE];

if (srce == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
write(1, buf, j);
j = 0;
}
if (srce != BUF_FLUSH)
buf[j++] = srce;
return (1);
}
