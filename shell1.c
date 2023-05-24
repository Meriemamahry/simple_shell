#include "shell.h"

/**
 * interactive - checks if the mode is interactive
 * @info: struct address
 *
 * Return: 1 or 0
 */
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - see if the character is delimiter
 * @c: the char
 * @delim_str: string delimiter
 * Return: 1 or 0
 */
int is_delim(char c, char *delim_str)
{
while (*delim_str)
if (*delim_str++ == c)
return (1);
return (0);
}

/**
 * _isalpha - see if the character is alphabetic
 * @c: character to input
 * Return: 1 or 0
 */

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
 * _atoi - string to integer
 * @s: string to be converted
 * Return: 0 or converted 
 */

int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;
if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
