#include "shell.h"

/**
 * _strlen - return the length of string
 * @k: a string
 * Return: the length
 */
int _strlen(char *k)
{
int length = 0;

if (!k)
return (0);
while (k[length] != '\0')
length++;
return (length);
}

/**
 * _strcmp - Compares 2 strings
 * @s1: a string
 * @s2: a string
 * Return: -1 or 1 or 0
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if c started with k
 * @c: a string
 * @k: a substring string
 * Return: Address
 */
char *starts_with(const char *c, const char *k)
{
while (*k)
if (*k++ != *c++)
return (NULL);
return ((char *)c);
}
/**
 * _strcat - Concatenates 2 strings
 * @k: a string(pointer)
 * @s: pointer (string)
 * Return: pointer
 */
char *_strcat(char *k, char *s)
{
char *i = k;

while (*k)
k++;
while (*s)
*k++ = *s++;
*k = *s;
return (i);
}
