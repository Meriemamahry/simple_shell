#include "main.h"
/**
 * list_path - create a list for direcories in the PATH
 * @env: environment variable
 * Return: pointer to a new list
 */
list_t *list_path(char **env)
{
	list_t *head = NULL;
	int i, len;
	char **j;

	len = 0;
	while (env[len])
		len++;
	j = malloc(sizeof(char *) * len);
	if (!j)
	{
		perror("MALLOC");
		return (NULL);
	}

	i = 0;
	while (env[i])
	{
		j[i] = str_dup(env[i]);
		i++;
	}

	head = create_list(j);

	i = 0;
	while (i < len)
	{
		free(j[i]);
		i++;
	}
	free(j);

	return (head);
}


/**
 * create_list - create a list for  direcories in the PATH
 * @environ: environment variable
 * Return: a pointer to the new list
 */
list_t *create_list(char **environ)
{
	list_t *head = NULL, *temp = NULL;
	int i = 0;
	char *name, *value = NULL;
	char *d, *aux;

	while (environ[i])
	{
		name = strtok(environ[i], "=");
		if (str_twins(name, "PATH") == 0)
		{
			value = strtok(NULL, "\n");
			break;
		}
		i++;
	}
	if (value)
	{
		i = 0;
		aux = strtok(value, ":");
		if (aux)
		{
			d = str_dup(aux);
			head = add_list(&head, d);
			aux = strtok(NULL, ":");
		}
		temp = head;
		while (aux)
		{
			i++;
			d = str_dup(aux);
			add_list(&head, d);
			temp = temp->next;
			aux = strtok(NULL, ":");
		}
	}
	else
		perror("ERROR: var_value NULL\n");

	return (head);
}

/**
 * add_list - add a new node
 * @head: pointer to list
 * @dir: string for the new node.
 * Return: pointer to list
 */
list_t *add_list(list_t **head, char *dir)
{
	list_t *new, *aux = *head;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		perror("ERROR: unable to allocate memory\n");
		return (NULL);
	}
	new->dir = dir;
	new->next = NULL;

	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * free_list - free the list of direcories.
 * @head: pinter to the list.
 */
void free_list(list_t *head)
{
	list_t *neext, *current;

	if (head)
	{
		current = head;
		neext = head->next;
		while (neext)
		{
			free(current->dir);
			free(neext);
			current = neext;
			neext = neext->next;
		}
		free(current->dir);
		free(current);
	}
}
