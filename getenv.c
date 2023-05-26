#include "shell.h"

/**
 * envget - returns the string 
 * @information: Structure containing poten
 * Return: 0
 */
char **envget(info_t *information)
{
if (!information->environ || information->env_changed)
{
information->environ = list_to_strings(information->env);
information->env_changed = 0;
}
return (information->environ);
}

/**
 * _envntset - Remove an environment 
 * @information: Structure containing potential arguments
 *  Return: 1 or 0
 * @varan: the string env var property
 */
int _envntset(info_t *information, char *varan)
{
list_t *nodeinfor = information->env;
size_t i = 0;
char *p;

if (!nodeinfor || !varan)
return (0);
while (nodeinfor)
{
p = starts_with(nodeinfor->str, varan);
if (p && *p == '=')
{
information->env_changed = delete_node_at_index(&(information->env), i);
i = 0;
nodeinfor = information->env;
continue;
}
nodeinfor = nodeinfor->next;
i++;
}
return (info->env_changed);
}

/**
 * _weset - Initialize a new environment
 * @information: Structure containing potential arguments
 * @varan: the string env var property
 * @value: the string env var value
 *  Return: 0
 */
int _weset(info_t *information, char *varan, char *value)
{
char *buff = NULL;
list_t *nodeinfor;
char *por;

if (!varan || !value)
return (0);
buff = malloc(_strlen(varan) + _strlen(value) + 2);
if (!buff)
return (1);
_strcpy(buff, varan);
_strcat(buff, "=");
_strcat(buff, value);
nodeinfor = information->env;
while (nodeinfor)
{
por = starts_with(nodeinfor->str, varan);
if (por && *por == '=')
{
free(nodeinfor->str);
nodeinfor->str = buff;
information->env_changed = 1;
return (0);
}
nodeinfor = nodeinfor->next;
}
add_node_end(&(information->env), buff, 0);
free(buff);
information->env_changed = 1;
return (0);
}
