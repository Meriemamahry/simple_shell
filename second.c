#include "main.h"
/**
 * check_syntax - checks the command separator syntax
 * @buffer: buffer to check
 * Return: 0 or -1 if the line contains a syntax error
 */
int check_syntax(char *buffer)
{
	int synt_error = 0;
	int i = 0;
	int j = 0;

	while (buffer[i])
	{
		if (buffer[i] == ';' && j == 1)
		{
			synt_error = -1;
			break;
		}
		else if (buffer[i] == ';' && j == 0)
		{
			j = 1;
		}
		else if (buffer[i] != ';' && buffer[i] != ' ' && j == 1)
		{
			j = 0;
		}
		i++;
	}

	return (synt_error);
}

/**
 * check_builtin - checks
 * @command: ....
 * Return: 0 or -1
 */
int check_builtin(char *command)
{
	if (!str_twins(command, "exit") || !str_twins(command, "env"))
		return (0);
	if (!str_twins(command, "help")
			return (0);
	return (-1);
}

/**
 * builtins - checking
 * @input: ...
 * @env: ...
 * Return: 0, 1 or -1 for error
 */
int builtins(char **input, char **env)
{
	char *a;
	int i = 0;

	if (!str_twins(input[0], "exit"))
	{
		free_argv(input);
		return (2);
	}
	if (!str_twins(input[0], "help"))
	{
		print_help(input);
		return (1);
	}
	if (!str_twins(input[0], "env"))
	{
		i = 0;

		while (env[i])
		{
			a = env[i];
			write(STDOUT_FILENO, a, str_len(a));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (0);
}

/**
 * print_help - print helping
 * @input: a buffer
 */
void print_help(char **input)
{
	char *a;

	if (input[1] != NULL)
	{
		if (!str_twins(input[1], "help"))
		{
			a = "help: help [pattern ...]\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\tDisplay information about builtin commands.\n\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\tDisplays brief summaries of builtin commands.  If PATTERN is\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\tspecified, gives detailed help on all commands matching PATTERN,";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\n\totherwise the list of help topics is printed.\n\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\tArguments:\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\t  PATTERN   Pattern specifiying a help topic\n";
			write(STDOUT_FILENO, a, str_len(a));
		}
		else if (!str_twins(input[1], "exit"))
		{
			a = "exit: exit\n";
			write(STDOUT_FILENO, a, str_len(a));
			a = "\tExit the shell.\n";
			write(STDOUT_FILENO, a, str_len(a));
		}
	}
	else
	{
		a = "These shell commands are defined internally.\n";
		write(STDOUT_FILENO, a, str_len(a));
		a = "Type `help name' to find out more about the function `name'.\n\n";
		write(STDOUT_FILENO, a, str_len(a));
		a = "help [pattern ...]\n";
		write(STDOUT_FILENO, a, str_len(a));
		a = " exit\n";
		write(STDOUT_FILENO, a, str_len(a));
	}
}
