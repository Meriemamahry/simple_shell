#include "main.h"
/**
 * str_len - give the length of a string
 * @s: string
 * Return: length of @s.
 */
int str_len(char *s)
{
	int i = 0, c = 0;

	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		c++;
		i++;
	}
	return (c);
}

/**
 * str_cpy - copy the string pointed to by src
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * str_dup - gives pointer to a new string which is a duplicate of str
 * @str: string to duplicate
 * Return: pointer to the duplicated string
 * 	  or NULL if str = NULL
 * 	  or if insufficient memory was available.
 */
char *str_dup(char *str)
{
	char *i;

	if (str == NULL)
		return (NULL);
	i = malloc(sizeof(char) * (str_len(str) + 1));
	if (i == NULL)
		return (NULL);
	return (str_cpy(i, str));
}
/**
 * *str_cat - concatenates 2 strings
 * @dest: destination
 * @src: source
 * Return: pointer to string dest
 */
char *str_cat(char *dest, char *src)
{
	int i, j;
	char *t = dest;

	if (src == NULL)
		return (t);
	for (i = 0; dest[i] != '\0'; i++)
	;
	for (j = 0; src[j] != '\0'; i++, j++)
		dest[i] = src[j];
	dest[i] = '\0';

	return (t);
}
/**
 * str_con - concatenate two strings into a new address
 * @s1: string to concatenate
 * @s2: string to concatenate
 * Return: memory address to the new string
 */
char *str_con(char *s1, char *s2)
{
	char *result;

	result = malloc(str_len(s1) + str_len(s2) + 1);
	if (!result)
	{
		perror("MALLOC");
		return (NULL);
	}

	str_cpy(result, s1);
	str_cat(result, s2);
	return (result);
}
