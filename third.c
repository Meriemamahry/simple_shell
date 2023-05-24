#include "main.h"
/**
 * create_argv - make the buffer to a vector
 * @input_buffer: buffer
 * @path: pointer to path list
 * Return: pointer
 */
char **create_argv(char *input_buffer, list_t **path)
{
	int i = 0, j = 0, argc = 1;
	char **argv;
	char *neew;
	char *current_str, *str_to_put;

	neew = get_path(input_buffer, path);
	while (neew[i])
	{
		if (neew[i] == ' ' &&
			(nee[i + 1] &&
				(neew[i + 1] != ' ' &&
					neew[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

	current_str = strtok(neew, "\n");
	current_str = strtok(current_str, " ");
	while (j < (argc + 1))
	{
		str_to_put = str_dup(current_str);
		argv[j] = str_to_put;
		current_str = strtok(NULL, " ");
		j++;

	}
	free(neew);
	return (argv);
}

/**
 * get_path - obtains directory path where command is executable
 * @buffer: the command
 * @path: pointer to path list
 * Return: directory with + buffer
 */
char *get_path(char *buffer, list_t **path)
{
	char *input;
	int *aux, *command = NULL;
	char *slashc, *slashi, *input_buffer;
	struct stat status;
	list_t *list_pointer = *path;

	input_buffer = clean_spaces(buffer);
	input = str_dup(input_buffer);
	free(input_buffer);

	aux = str_dup(input);
	command = strtok(aux, " ");
	if (command == NULL)
		command = aux;
	if (stat(command, &status) == 0)
	{
		free(aux);
		return (input);
	}
	if (check_builtin(command) == 0)
	{
		free(aux);
		return (input);
	}
	slashc = str_con("/", command);
	slashi = str_con("/", input);

	free(aux);
	return (aux_get_path(list_pointer, slashc, slashi, input));
}


/**
 * aux_get_path - auxiliary function to get directory path
 * @list_pointer: pointer to directory in path list.
 * @slash_command: aux string
 * @slash_input: aux string
 * @input: aux string
 * Return: directory +  buffer
 */
char *aux_get_path(list_t *list_pointer, char *slash_command,
			char *slash_input, char *input)
{
	char *j;
	struct stat status;

	while (list_pointer)
	{
		j = str_con(list_pointer->dir, slash_command);
		if (stat(j, &status) == 0)
			break;
		free(j);
		list_pointer = list_pointer->next;
	}
	if (list_pointer && (stat(j, &status) == 0))
	{
		free(j);
		j = str_con(list_pointer->dir, slash_input);
		free(input);
		free(slash_input);
		free(slash_command);
		return (j);
	}
	free(slash_input);
	free(slash_command);
	return (input);
}

/**
 * clean_spaces - remove spaces in the first position
 * @buffer: buffer
 * Return: a new buffer
 */
char *clean_spaces(char *buffer)
{
	int len;
	int position;
	int i = 0;
	char *new_buffer, *tbuffer;

	new_buffer = str_dup(buffer);
	if (new_buffer[0] != ' ')
		return (new_buffer);
	while (new_buffer[i] == ' ')
		i++;
	position = i;
	while (new_buffer[i])
		i++;
	len = i - position;
	tbuffer = malloc(sizeof(char) * (len + 1));
	i = position;
	while (new_buffer[i])
	{
		tbuffer[i - position] = new_buffer[i];
		i++;
	}
	tbuffer[i - position] = '\0';
	free(new_buffer);
	return (tbuffer);
}

/**
 * free_argv - frees memory
 * @argv: argument vector
 */
void free_argv(char **argv)
{
	int i = 0;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
