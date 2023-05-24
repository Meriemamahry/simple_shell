#include "shell.h"

/**
 **_memset - constant byte
 *@s: the pointer
 *@byt: the byte
 *@n: the amount of bytes to be filled
 *Return: pointer
 */
char *_memset(char *s, char byt, unsigned int n)
{
unsigned int k;

for (k = 0; k < n; k++)
s[k] = byt;
return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
 * _realloc - reallocates
 * @ptr: pointer to pre
 * @old_size: byte size
 * @new_size: byte size
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *po;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
po = malloc(new_size);
if (!po)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
po[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (po);
}
