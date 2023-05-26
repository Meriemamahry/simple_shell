#include "shell.h"
/**
 * is_exec - checking if it s executable command
 * @i: structure
 * @pt: path
 * Return: 1 or 0
 */
int is_exec(info_t *i, char *pt)
{
struct stat t;

(void)i;
if (!pt || stat(pt, &t))
{
return (0);
}
if (t.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @pt: path
 * @deb: index of begnning
 * @f: index
 * Return: a pointer
 */
char *duplicate_chars(char *pt, int deb, int f)
{
static char buf[1024];
int i = 0, j = 0;

for (j = 0, i = deb; i < f; i++)
if (pt[i] != ':')
buf[j++] = pt[i];
buf[j] = 0;
return (buf);
}

/**
 * findPath - return the path of command
 * @i: structure
 * @pt: path
 * @command: command to find path
 * Return: return the path
 */
char *findPath(info_t *i, char *pt, char *command)
{
int k = 0, pos = 0;
char *path;

if (!pt)
return (NULL);
if ((_strlen(command) > 2) && starts_with(command, "./"))
{
if (is_exec(i, command))
return (command);
}
while (1)
{
if (!pt[k] || pt[k] == ':')
{
path = duplicate_chars(pt, pos, k);
if (!*path)
_strcat(path, command);
else
{
_strcat(path, "/");
_strcat(path, command);
}
if (is_exec(i, path))
return (path);
if (!pt[k])
break;
pos = k;
}
k++;
}
return (NULL);
}
