#include "main.h"

/**
 * ctrl_c - detect the CTRL+C signal and print another line
 * @x: ...
 */
void ctrl_c(__attribute__((unused)) int x)
{
	signal(SIGINT, ctrl_c);
	write(1, "\n", 1);
	write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
}
/**
 * print_error - print errors to standard output
 * @program_name: argv[0]
 * @input: command that produces the error
 * @error_num: error number
 */
void print_error(char *program_name, char *input, int error_num)
{
	char *str;

	if (error_num == 127)
	{
		write(STDOUT_FILENO, program_name, str_len(program_name));
		write(STDOUT_FILENO, ": 1: ", 5);
		write(STDOUT_FILENO, input, str_len(input));
		write(STDOUT_FILENO, ": not found\n", 12);
	}
	if (error_num == 2)
	{
		str = "sh: 1: Syntax error: \"";
		write(STDOUT_FILENO, str, str_len(str));
		write(STDOUT_FILENO, ";", 1);
		str = "\" unexpected\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
	if (error_num == 3)
	{
		write(STDOUT_FILENO, program_name, str_len(program_name));
		write(STDOUT_FILENO, ": 1: ", 5);
		str = "internal error allocating memory\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
}
