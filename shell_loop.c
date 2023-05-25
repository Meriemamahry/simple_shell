#include "shell.h"

/**
 * hsh - main shell
 * @info: the parameter
 * @av: the argument
 * Return: 0 or 1 or error code
 */
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (intera(info))
_puts("$ ");
ptu_char(BUF_FLUSH);
r = getIn(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (intera(info))
_putchar('\n');
free_info(info, 0);
}
writeHistory(info);
free_info(info, 1);
if (!intera(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
 * find_builtin - builtin command
 * @info: the parameter
 * Return: -1 or 1 or 0 or -2
 */
int find_builtin(info_t *info)
{
int i, built_in = -1;
builtin_table builtintbl[] = {
{"exit", exiit},
{"env", _myenv},
{"help", _ch},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", change_dir},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in = builtintbl[i].func(info);
break;
}
return (built_in);
}

/**
 * find_cmd - command in PATH
 * @info: the parameter
 * Return: void
 */
void find_cmd(info_t *info)
{
char *path = NULL;
int i, m;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, m = 0; info->arg[i]; i++)
if (!delim(info->arg[i], " \t\n"))
m++;
if (!m)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((intera(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
printerr(info, "not found\n");
}
}
}

/**
 * fork_cmd - forks
 * @info: the parameter
 * Return: void
 */
void fork_cmd(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
printerr(info, "Permission denied\n");
}
}
}
