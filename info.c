#include "shell.h"

/**
 * clearation - initializes info_t struct
 * @information: struct address
 */
void clearation(info_t *information)
{
information->arg = NULL;
information->argv = NULL;
information->path = NULL;
information->argc = 0;
}

/**
 * setaion - initializes info_t struct
 * @info: struct address
 * @avera: argument vector
 */
void setaion(info_t *information, char **avera)
{
int i = 0;

information->fname = avera[0];
if (information->arg)
{
information->argv = strtw(information->arg, " \t");
if (!information->argv)
{
information->argv = malloc(sizeof(char *) * 2);
if (information->argv)
{
information->argv[0] = _strdup(information->arg);
information->argv[1] = NULL;
}
}
for (i = 0; information->argv && information->argv[i]; i++)
information->argc = i;
replace_alias(information);
replace_vars(information);
}
}

/**
 * freation - frees info_t struct fields
 * @information: struct address
 * @allocez: true if freeing all fields
 */
void freation(info_t *information, int allocez)
{
forfr(information->argv);
information->argv = NULL;
information->path = NULL;
if (allocez)
{
if (!information->cmd_buf)
free(information->arg);
if (information->env)
freelist(&(information->env));
if (information->history)
freelist(&(information->history));
if (information->alias)
freelist(&(information->alias));
forfr(information->environ);
information->environ = NULL;
f_ree((void **)information->cmd_buf);
if (information->readfd > 2)
close(information->readfd);
_putchar(BUF_FLUSH);
}
}
