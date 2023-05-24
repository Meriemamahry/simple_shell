#include "shell.h"
/**
 * _myenv - prints environment
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
 * @name: name of env var
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	char *s;
	list_t *node = info->env;

	while (node)
	{
		s = starts_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env
 * @info: Structure
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	size_t s;
	list_t *node = NULL;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	info->env = node;
	return (0);
}
