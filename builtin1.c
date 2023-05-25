#include "shell.h"
/**
 * hist - gives the history list
 * @i: Structure
 *  Return: 0
 */
int hist(info_t *i)
{
	printList(i->history);
	return (0);
}
/**
 * unsetAlias - unsets alias => string
 * @i: structure
 * @s: string
 * Return: 0 or 1 on error
 */
int unsetAlias(info_t *i, char *s)
{
	char *p, t;
	int k;

	p = str_chr(s, '=');
	t = *p;
	if (!p)
	{
		return (1);
	}
	*p = 0;
	k = delete_node_at_index(&(i->alias),
		get_node_index(i->alias, node_starts_with(i->alias, s, -1)));
	*p = t;
	return (k);
}

/**
 * setAlias - Sets alias to string
 * @i: structure
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *i, char *s)
{
	char *t;

	t = str_chr(s, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (unsetAlias(i, s));
	unsetAlias(i, s);
	return (add_node_end(&(i->alias), s, 0) == NULL);
}

/**
 * printAlias - Prints an alias
 * @n: alias node
 * Return: Always 0 or 1 on error
 */
int printAlias(list_t *n)
{
	char *p = NULL, *t = NULL;

	if (n)
	{
		p = str_chr(n->str, '=');
		for (t = n->str; t <= p; t++)
		{
			_putchar(*t);
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * monAlias - man alias
 * @i: Structure
 *  Return: 0
 */
int monAlias(info_t *i)
{
	int k = 0;
	char *p = NULL;
	list_t *t = NULL;

	if (info->argc == 1)
	{
		t = i->alias;
		while (t)
		{
			printAlias(t);
			t = t->next;
		}
		return (0);
	}
	for (k = 1; i->argv[k]; k++)
	{
		p = str_chr(i->argv[k], '=');
		if (p)
		{
			setAlias(i, i->argv[k]);
		}
		else
		{
			printAlias(node_starts_with(i->alias, i->argv[k], '='));
		}
	}

	return (0);
}
