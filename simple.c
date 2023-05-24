#include "main.h"
/**
 * main - execute the  mode
 * @ac:count
 * @av:vector
 * @env: environment var
 * Return: 0
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
	list_t *p;
	char *prog_name = av[0];
	int i, mode = 0;

	signal(SIGINT, SIG_IGN);
	p = list_path(env);
	if (isatty(0))
		mode = 1;
	i = start_shell(p, env, prog_name, mode);
	free_list(p);
	return (i);
}

/**
 * start_shell - runs an interactive shell
 * @path: pointer to the list of the PATH
 * @env: environment variable
 * @program_name: argv[0]
 * @mode: specify the mode.
 * Return: 0
 */
int start_shell(list_t *path, char **env, char *program_name, int mode)
{
	char *buffer = NULL;
	int s, line_s;
	size_t len = 0;

	while (1)
	{
		if (mode == 1)
			write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
		signal(SIGINT, ctrl_c);
		line_s = getline(&buffer, &len, stdin);
		if (line_s == -1)
		{
			if (line_s == EOF)
			{
				free(buffer);
				if (mode == 1)
					write(STDOUT_FILENO, "\n", 1);
				return (s);
			}
			print_error(program_name, buffer, 3);
		}
		s = execute_buffer(buffer, path, env, program_name);
		if (s == -1 || s == 127 || s == 2)
		{
			if (s == -1)
				perror("COMMAND NOT FOUND");
			free(buffer);
			break;
		}
	}
	return (s);
}

/**
 * execute_buffer - executes a command line
 * @buffer: command line
 * @path: pointer to the list of  PATH
 * @env: environment variable
 * @program_name: argv[0]
 * Return: 0
 */
int execute_buffer(char *buffer, list_t *path, char **env, char *program_name)
{
	char *buffert, *input, *new_buffer;
	int aux, final, exe_result = 0;

	buffert = clean_comments(buffer);
	input = str_tr(buffert, '\t', ' ');
	if (not_empty(input))
	{
		final = str_count(input, ';');
		if (final > 1)
		{
			aux = check_syntax(input);
			if (aux == -1)
			{
				print_error(program_name, input, 2);
				free(input);
				return (-1);
			}
			new_buffer = str_tr(input, ';', '\n');
		}
		else
			new_buffer = str_dup(input);

		exe_result = execute_command(new_buffer, path, env, final, program_name);
		free(new_buffer);
	}
	free(input);
	free(buffert);
	return (exe_result);
}

/**
 * execute_command - run a command
 * @new_buffer: command line
 * @path: pointer to the list the PATH
 * @env: environment variable
 * @final: total number of separate commands
 * @program_name: argv[0]
 * Return: 0 , 1 if the command not found or 2 exit command
 */
int execute_command(char *new_buffer, list_t *path, char **env,
			int final, char *program_name)
{
	char *tmp_buffer, *current_buffer;
	char **input;
	int i, aux, current, exe_result = 0;

	current = 0;
	while (current < final)
	{
		tmp_buffer = str_dup(new_buffer);
		current_buffer = strtok(tmp_buffer, "\n");
		for (i = 0; i < current; i++)
			current_buffer = strtok(NULL, "\n");
		input = create_argv(current_buffer, &path);
		aux = builtins(input, env);
		if (aux == 2)
		{
			free(tmp_buffer);
			return (2);
		}
		if (aux == 0)
		{
			exe_result = execute_fork(input, program_name);
		}
		free_argv(input);
		free(tmp_buffer);
		current++;
	}
	return (exe_result);
}

/**
 * execute_fork - auxiliar function for execute_command.
 * @input: argv to execute
 * @program_name: argv[0]
 * Return: 0 or 127 if command not found
 */
int execute_fork(char **input, char *program_name)
{
	int status, exe_result = 0;
	struct stat stat_status;
	pid_t pid = getpid();

	pid = fork();
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
		{
			print_error(program_name, input[0], 127);
			exe_result = 127;
		}
	}
	else
	{
		wait(&status);
		if (stat(input[0], &stat_status) == -1)
			exe_result = 127;
	}

	return (exe_result);
}
