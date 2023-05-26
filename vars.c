#include "shell.h"

/**
 * washchaine - test chain delimiter
 * @information: struct
 * @buf: the char buffer
 * @p: address of buf
 * Return: 1 or 0
 */
int washchaine(info_t *information, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
information->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
information->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
information->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
 * check_chain - checks last status
 * @informa: struct
 * @buf: the char buffer
 * @p: address of current position
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(info_t *informa, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (informa->cmd_buf_type == CMD_AND)
{
if (informa->status)
{
buf[i] = 0;
j = len;
}
}
if (informa->cmd_buf_type == CMD_OR)
{
if (!informa->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}

/**
 * replace_alias - tokenized string
 * @information: the parameter
 * Return: 1 or 0
 */
int replace_alias(info_t *information)
{
int i;
list_t *nodetqwd;
char *p;

for (i = 0; i < 10; i++)
{
nodetqwd = nodetabda(information->alias, information->argv[0], '=');
if (!nodetqwd)
return (0);
free(information->argv[0]);
p = str_chr(nodetqwd->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
information->argv[0] = p;
}
return (1);
}

/**
 * replace_vars - replaces vars
 * @information: struct
 * Return: 1 or 0
 */
int replace_vars(info_t *information)
{
int i = 0;
list_t *nodetqwd;

for (i = 0; information->argv[i]; i++)
{
if (information->argv[i][0] != '$' || !information->argv[i][1])
continue;
if (!_strcmp(information->argv[i], "$?"))
{
bdlstr(&(information->argv[i]),
_strdup(convnum(information->status, 10, 0)));
continue;
}
if (!_strcmp(information->argv[i], "$$"))
{
bdlstr(&(information->argv[i]),
_strdup(convnum(getpid(), 10, 0)));
continue;
}
nodetqwd = nodetabda(information->env, &information->argv[i][1], '=');
if (nodetqwd)
{
bdlstr(&(information->argv[i]),
_strdup(str_chr(nodetqwd->str, '=') + 1));
continue;
}
bdlstr(&information->argv[i], _strdup(""));
}
return (0);
}

/**
 * bdlstr - replaces string in the code
 * @oldstr: old string
 * @newstr: new string
 * Return: 1 or 0
 */
int bdlstr(char **oldstr, char *newstr)
{
free(*oldstr);
*oldstr = newstr;
return (1);
}
