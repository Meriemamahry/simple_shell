#include "main.h"

/**
 * check_syntax - checks syntax 
 * @buffer: buffer
 * Return: 0 or -1 if the line contains a syntax error
 */
int check_syntax(char *buffer)
{
	int flag = 0;
	int error = 0;
	int i = 0;

	while (buffer[i])
	{
		if (buffer[i] == ';' && flag == 1)
		{
			error = -1;
			break;
		}
		else if (buffer[i] == ';' && flag == 0)
		{
			flag = 1;
		}
		else if (buffer[i] != ';' && buffer[i] != ' ' && flag == 1)
		{
			flag = 0;
		}
		i++;
	}

	return (error);
}

/**
 * check_builtin - checks
 * @command: ...
 * Return: 0 , -1 sinon
 */
int check_builtin(char *command)
{
	if (!str_twins(command, "exit") || !str_twins(command, "env") || !str_twins(command, "help"))
		return (0);
	return (-1);
}

/**
 * builtins - check
 * @input: ...
 * @env: ....
 * Return: 0 or 1 or -1 
 */
int builtins(char **input, char **env)
{
	int i = 0;
	char *str;

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
			str = env[i];
			write(STDOUT_FILENO, str, str_len(str));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (0);
}

/**
 * print_help - print help
 * @input: buffer
 */
void print_help(char **input)
{
	char *str;

	if (input[1] != NULL)
	{
		if (!str_twins(input[1], "help"))
		{
			str = "help: help [pattern ...]\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tDisplay information about builtin commands.\n\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tDisplays brief summaries of builtin commands.  If PATTERN is\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tspecified, gives detailed help on all commands matching PATTERN,";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\n\totherwise the list of help topics is printed.\n\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tArguments:\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\t  PATTERN   Pattern specifiying a help topic\n";
			write(STDOUT_FILENO, str, str_len(str));
		}
		else if (!str_twins(input[1], "exit"))
		{
			str = "exit: exit\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tExit the shell.\n";
			write(STDOUT_FILENO, str, str_len(str));
		}
	}
	else
	{
		str = "These shell commands are defined internally.\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = "Type `help name' to find out more about the function `name'.\n\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = " help [pattern ...]\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = " exit\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
}
