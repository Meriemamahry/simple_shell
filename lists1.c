#include "shell.h"

/**
 * tollist - determines length of l list
 * @heado: pointer to first node
 * Return: size of list
 */
size_t tollist(const list_t *heado)
{
size_t i = 0;

while (heado)
{
heado = heado->next;
i++;
}
return (i);
}

/**
 * ilastring - returns an array of strings of the list->str
 * @heado: pointer to first node
 * Return: array of strings
 */
char **ilastring(list_t *heado)
{
list_t *nodetqwd = heado;
size_t i = tollist(heado), j;
char **strs;
char *str;

if (!heado || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; nodetqwd; nodetqwd = nodetqwd->next, i++)
{
str = malloc(_strlen(nodetqwd->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, nodetqwd->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
 * printListing - prints all elem
 * @heado: pointer to first nod
 * Return: size of list
 */
size_t printListing(const list_t *heado)
{
size_t i = 0;

while (heado)
{
_puts(convnum(heado->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(heado->str ? heado->str : "(nil)");
_puts("\n");
heado = heado->next;
i++;
}
return (i);
}

/**
 * nodetabda - returns node whose string starts
 * @nodetqwd: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: null
 */
list_t *nodetabda(list_t *nodetqwd, char *prefix, char c)
{
char *p = NULL;

while (nodetqwd)
{
p = starts_with(nodetqwd->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * ijbadnode - gets the index of
 * @heado: pointer to list
 * @nodetqwd: pointer to the n
 * Return: index
 */
ssize_t ijbadnode(list_t *heado, list_t *nodetqwd)
{
size_t i = 0;

while (heado)
{
if (heado == nodetqwd)
return (i);
heado = heado->next;
i++;
}
return (-1);
}
