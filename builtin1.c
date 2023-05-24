#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: Structure
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: structure
 * @str:  string alias
 *
 * Return: Always 0 or 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	int i;
	char *s, c;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	c = *s;
	*s = 0;
	i = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = c;
	return (i);
}

/**
 * set_alias - sets alias to string
 * @info: structure
 * @str: the string alias
 * Return: 0 or 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 * Return: 0 or 1 on error
 */
int print_alias(list_t *node)
{
	char *s = NULL;
	char *k = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (k = node->str; k <= s; k++)
			_putchar(*k);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - man alias
 * @info: Structure
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		if (_strchr(info->argv[i], '='))
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
