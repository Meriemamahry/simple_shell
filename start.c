#include "main.h"
/**
 * main - execute interactive or non-interactive mode
 * @ac: counting
 * @av: a vector
 * @env: environment variable.
 * Return: 0
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
	list_t *path;
	char *program = av[0];
	int i;
	int mode = 0;

	signal(SIGINT, SIG_IGN);
	path = list_path(env);
	if (isatty(0))
		mode = 1;
	i = start_shell(path, env, program, mode);
	free_list(path);
	return (i);
}

/**
 * start_shell - runs the interactive shell
 * @path: pointer to the list of the PATH
 * @env: environment variable
 * @program_name: argv[0]
 * @mode: specify the mode.
 * Return: 0
 */
int start_shell(list_t *path, char **env, char *program_name, int mode)
{
	char *b = NULL;
	int line;
	int s;
	size_t len = 0;

	while (1)
	{
		if (mode == 1)
			write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
		signal(SIGINT, ctrl_c);
		line = getline(&b, &len, stdin);
		if (line == -1)
		{
			if (line == EOF)
			{
				free(b);
				if (mode == 1)
					write(STDOUT_FILENO, "\n", 1);
				return (s);
			}
			print_error(program_name, b, 3);
		}
		s = execute_buffer(b, path, env, program_name);
		if (s == -1 || s == 127 || s == 2)
		{
			if (s == -1)
				perror("COMMAND NOT FOUND");
			free(b);
			break;
		}
	}
	return (s);
}

/**
 * execute_buffer - execute the command line
 * @buffer: command line to execute
 * @path: pointer to the list of the PATH.
 * @env: environment variable
 * @program_name: argv[0]
 * Return: 0
 */
int execute_buffer(char *buffer, list_t *path, char **env, char *program_name)
{
	char *neew;
	char *input;
	char *buffertr;
	int i, final, result = 0;

	buffertr = clean_comments(buffer);
	input = str_tr(buffertr, '\t', ' ');
	if (not_empty(input))
	{
		final = str_count(input, ';');
		if (final > 1)
		{
			i = check_syntax(input);
			if (i == -1)
			{
				print_error(program_name, input, 2);
				free(input);
				return (-1);
			}
			neew = str_tr(input, ';', '\n');
		}
		else
			neew = str_dup(input);

		result = execute_command(neew, path, env, final, program_name);
		free(neew);
	}
	free(input);
	free(buffertr);
	return (result);
}

/**
 * execute_command - run a command
 * @new_buffer: command line to execute
 * @path: pointer to the list of the PATH
 * @env: environment variable
 * @final: total number of commands
 * @program_name: argv[0]
 * Return: 0 , 1 if the command not found or 2 =>exit command
 */
int execute_command(char *new_buffer, list_t *path, char **env,
			int final, char *program_name)
{
	char *temp_buffer, *current_buffer;
	char **input;
	int i, aux, current;
	int result = 0;

	current = 0;
	while (current < final)
	{
		temp_buffer = str_dup(new_buffer);
		current_buffer = strtok(temp_buffer, "\n");
		for (i = 0; i < current; i++)
			current_buffer = strtok(NULL, "\n");
		input = create_argv(current_buffer, &path);
		aux = builtins(input, env);
		if (aux == 2)
		{
			free(temp_buffer);
			return (2);
		}
		if (aux == 0)
		{
			result = execute_fork(input, program_name);
		}
		free_argv(input);
		free(temp_buffer);
		current++;
	}
	return (result);
}

/**
 * execute_fork - auxiliar function for execute_command.
 * @input: argv
 * @program_name: argv[0]
 * Return: 0 or 127 if the command not found
 */
int execute_fork(char **input, char *program_name)
{
	int status;
	int result = 0;
	struct stat stat_status;
	pid_t pid = getpid();

	pid = fork();
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
		{
			print_error(program_name, input[0], 127);
			result = 127;
		}
	}
	else
	{
		wait(&status);
		if (stat(input[0], &stat_status) == -1)
			result = 127;
	}

	return (result);
}
