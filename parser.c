#include "shell.h"

/**
 * is_cmd - checks file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Return: 1 or 0
 */
int is_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dup_chars - duplicates characters in the string
 * @pathst: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer
 */
char *dup_chars(char *pathst, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathst[i] != ':')
buf[k++] = pathst[i];
buf[k] = 0;
return (buf);
}

/**
 * find_path - find cmd path
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int c = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[c] || pathstr[c] == ':')
{
path = dup_chars(pathstr, curr_pos, c);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
return (path);
if (!pathstr[c])
break;
curr_pos = c;
}
c++;
}
return (NULL);
}
