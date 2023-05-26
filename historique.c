#include "shell.h"

/**
 * getHistory - gets history
 * @i: struct
 * Return: string
 */

char *getHistory(info_t *i)
{
char *c, *d;

d = _getenviron(i, "HOME=");
if (!d)
return (NULL);
c = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
if (!c)
return (NULL);
c[0] = 0;
_strcpy(c, d);
_strcat(c, "/");
_strcat(c, HIST_FILE);
return (c);
}

/**
 * writeHistory - creates a file
 * @i: structure
 * Return: 1 or -1
 */
int writeHistory(info_t *i)
{
list_t *n = NULL;
ssize_t f;
char *file_name = getHistory(i);

if (!file_name)
return (-1);
f = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);
if (f == -1)
return (-1);
for (n = i->history; n; n = n->next)
{
_fds(n->str, f);
_fdt('\n', f);
}
_fdt(BUF_FLUSH, f);
close(f);
return (1);
}

/**
 * readHistory - Reads history
 * @i: structure
 * Return: histcount on success or 0
 */
int readHistory(info_t *i)
{
int k, last = 0, linecount = 0;
ssize_t fd, rdlen, f_size = 0;
struct stat st;
char *buf = NULL, *filename = getHistory(i);

if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
f_size = st.st_size;
if (f_size < 2)
return (0);
buf = malloc(sizeof(char) * (f_size + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, f_size);
buf[f_size] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (k = 0; k < f_size; k++)
if (buf[k] == '\n')
{
buf[k] = 0;
buildHistory(i, buf + last, linecount++);
last = k + 1;
}
if (last != k)
buildHistory(i, buf + last, linecount++);
free(buf);
i->histcount = linecount;
while (i->histcount-- >= HIST_MAX)
supprimerlist(&(i->history), 0);
renumberHistory(i);
return (i->histcount);
}

/**
 * buildHistory - adds input to a history
 * @i: Structure
 * @b: char
 * @count: histcount
 * Return:  0
 */
int buildHistory(info_t *i, char *b, int count)
{
list_t *n = NULL;

if (i->history)
n = i->history;
ajouter_fin(&n, b, count);
if (!i->history)
i->history = n;
return (0);
}

/**
 * renumberHistory - renumbers the history
 * @i: Structure
 * Return: new histcount
 */
int renumberHistory(info_t *i)
{
int k = 0;
list_t *n = i->history;

while (n)
{
n->num = k++;
n = n->next;
}
return (i->histcount = k);
}
