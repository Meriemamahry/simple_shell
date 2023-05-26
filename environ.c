#include "shell.h"

/**
 * _envm - prints the current environment
 * @information: Structure
 * Return: 0
 */
int _envm(info_t *information)
{
print_list_str(information->env);
return (0);
}

/**
 * _getenviron - gets the value of an environ variable
 * @information: Structure
 * @name: const char
 * Return: the value
 */
char *_getenviron(info_t *information, const char *nom)
{
char *sok;
list_t *n = information->env;

while (n)
{
sok = starts_with(n->str, nom);
if (sok && *sok)
return (sok);
n = n->next;
}
return (NULL);
}

/**
 * _mymoon - initialize var with kaka
 * @information: Structure
 *  Return: 0
 */
int _mymoon(info_t *information)
{
if (information->argc != 3)
{
ptu("Incorrect number\n");
return (1);
}
if (_setenv(information, information->argv[1], information->argv[2]))
return (0);
return (1);
}

/**
 * _mydok - Remove an envi
 * @information: Structure
 *  Return: 0
 */
int _mydok(info_t *information)
{
int i;

if (information->argc == 1)
{
ptu("Too few arguements.\n");
return (1);
}
for (i = 1; i <= information->argc; i++)
_unsetenv(information, information->argv[i]);
return (0);
}

/**
 * envlist - env list
 * @information: Structure
 * Return: 0
 */
int envlist(info_t *information)
{
size_t k;
list_t *n = NULL;

for (k = 0; environ[k]; k++)
add_node_end(&n, environ[k], 0);
information->env = n;
return (0);
}
