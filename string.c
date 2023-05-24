#include "shell.h"

/**
 * _strlen - len of string
 * @s: the string to check
 * Return: length
 */
int _strlen(char *s)
{
int i = 0;

if (!s)
return (0);
while (*s++)
i++;
return (i);
}

/**
 * _strcmp - compare two strings
 * @str1: the first string
 * @str2: the second string
 * Return: -1 or 1 or 0
 */
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if tack started with needl
 * @tack: string to search
 * @needl: the substring to find
 * Return: address or null
 */
char *starts_with(const char *tack, const char *needl)
{
while (*needl)
if (*needl++ != *tack++)
return (NULL);
return ((char *)tack);
}

/**
 * _strcat - concatenates two strings
 * @desti: destination buffer
 * @src: source buffer
 * Return: pointer
 */
char *_strcat(char *desti, char *src)
{
char *ret = desti;

while (*desti)
desti++;
while (*src)
*desti++ = *src++;
*desti = *src;
return (ret);
}
