#include "shell.h"

/**
 **_strncpy - make a copy of a string
 *@deststr: the final destination of the copied string
 *@src: the original string
 *@n: the length of string copied
 *Return: string
 */
char *_strncpy(char *deststr, char *src, int n)
{
int i, j;
char *s = deststr;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
deststr[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
deststr[j] = '\0';
j++;
}
}
return (s);
}

/**
 **_strncat - concatenates two strings
 *@deststr: string number 1
 *@src: string number 2
 *@n: max amount of bytes to be used
 *Return: string
 */
char *_strncat(char *deststr, char *src, int n)
{
int i, j;
char *s = deststr;

i = 0;
j = 0;
while (deststr[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
deststr[i] = src[j];
i++;
j++;
}
if (j < n)
deststr[i] = '\0';
return (s);
}

/**
 **_strchr - looks for character in a string
 *@s: the string to be parsed
 *@c: the character searched
 *Return: pointer
 */
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
}
