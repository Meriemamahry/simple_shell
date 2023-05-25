#include "shell.h"
/**
 * **strtw - separate string
 * @c: string
 * @d: the delimeter string
 * Return: a pointer ,or null
 */

char **strtw(char *c, char *d)
{
	int i, j, k, m, n = 0;
	char **s;

	if (c == NULL || c[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; c[i] != '\0'; i++)
		if (!delim(c[i], d) && (delim(c[i + 1], d) || !c[i + 1]))
			n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (delim(c[i], d))
			i++;
		k = 0;
		while (!delim(c[i + k], d) && c[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = c[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strt2 - splits string
 * @c: a string
 * @d: a char
 * Return: pointer
 */
char **strt2(char *c, char d)
{
char **s;
int i, j, k, m, n = 0;

if (c == NULL || c[0] == 0)
return (NULL);
for (i = 0; c[i] != '\0'; i++)
if ((c[i] != d && c[i + 1] == d) ||
(c[i] != d && !c[i + 1]) || c[i + 1] == d)
n++;
if (n == 0)
return (NULL);
s = malloc((1 + n) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < n; j++)
{
while (c[i] == d && c[i] != d)
i++;
k = 0;
while (c[i + k] != d && c[i + k] && c[i + k] != d)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = c[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
