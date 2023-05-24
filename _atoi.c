#include "shell.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @info: address
 *
 * Return: 1 or 0
 */
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - see if character is delimiter
 * @i: char checked
 * @delim: the delimeter string
 * Return: 1 or 0
 */
int is_delim(char i, char *delim)
{
while (*delim)
if (*delim++ == i)
return (1);
return (0);
}

/**
 *_isalpha - see if character is alpha
 *@i: The character to input
 *Return: 1 or 0
 */

int _isalpha(int i)
{
if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
return (1);
else
return (0);
}

/**
 *_atoi - take a string and convert it to int
 *@str: string to be converted
 *Return: 0 or converted number
 */

int _atoi(char *str)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  str[i] != '\0' && flag != 2; i++)
{
if (str[i] == '-')
sign *= -1;
if (str[i] >= '0' && str[i] <= '9')
{
flag = 1;
result *= 10;
result += (str[i] - '0');
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
