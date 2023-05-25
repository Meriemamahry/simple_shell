#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure
 *@name: const char
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	char *s;
	list_t *n = info->env;

	while (n)
	{
		s = starts_with(n->str, name);
		if (s && *s)
			return (s);
		n = n->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize var
 * @info: Structure
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		ptu("Incorrect number\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an envi variable
 * @info: Structure
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		ptu("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - env list
 * @info: Structure
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	size_t i;
	list_t *n = NULL;

	for (i = 0; environ[i]; i++)
		add_node_end(&n, environ[i], 0);
	info->env = n;
	return (0);
}
