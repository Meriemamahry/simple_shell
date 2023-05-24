#include "main.h"
/**
 * main - execute code with betty style
 * @ac:argumen count
 * @av:argument vector
 * @env: environment variable global.
 * Return: 0(success)
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
list_t *path;
char *program_name = av[0];
int aux, mode = 0;

signal(SIGINT, SIG_IGN);
path = list_path(env);
if (isatty(0))
mode = 1;
aux = start_shell(path, env, program_name, mode);
free_list(path);
return (aux);
}

/**
 * start_shell - start the shell
 * @path: take the path of current directory
 * @env: environment variable
 * @program_name: argv[0] of main
 * @mode: choose mode
 * Return: 0
 */
int start_shell(list_t *path, char **env, char *program_name, int mode)
{
char *buffer = NULL;
int status, line_status;
size_t len = 0;

while (1)
{
if (mode == 1)
write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
signal(SIGINT, ctrl_c);
line_status = getline(&buffer, &len, stdin);
if (line_status == -1)
{
if (line_status == EOF)
{
free(buffer);
if (mode == 1)
write(STDOUT_FILENO, "\n", 1);
return (status);
}
print_error(program_name, buffer, 3);
}
status = execute_buffer(buffer, path, env, program_name);
if (status == -1 || status == 127 || status == 2)
{
if (status == -1)
perror("COMMAND NOT FOUND");
free(buffer);
break;
}
}
return (status);
}

/**
 * execute_buffer - runs the command line
 * @buffer: executed command line
 * @path: point to the current dir
 * @env: environment variable
 * @program_name: argv[0] of main
 * Return: 0 (success)
 */
int execute_buffer(char *buffer, list_t *path, char **env, char *program_name)
{
char *buffer_tr, *input_buffer, *new_buffer;
int aux, final, exe_result = 0;

buffer_tr = clean_comments(buffer);
input_buffer = str_tr(buffer_tr, '\t', ' ');
if (not_empty(input_buffer))
{
final = str_count(input_buffer, ';');
if (final > 1)
{
aux = check_syntax(input_buffer);
if (aux == -1)
{
print_error(program_name, input_buffer, 2);
free(input_buffer);
return (-1);
}
new_buffer = str_tr(input_buffer, ';', '\n');
}
else
new_buffer = str_dup(input_buffer);
exe_result = execute_command(new_buffer, path, env, final, program_name);
free(new_buffer);
}
free(input_buffer);
free(buffer_tr);
return (exe_result);
}

/**
 * execute_command - executes command
 * @new_buffer: executed command line
 * @path: point to the current path
 * @env: environment variable
 * @final: number of separate commands
 * @program_name: argv[0] of main
 * Return: 0 or 1, or 2 (exit command)
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
 * execute_fork - execute fork function
 * @input: argv to execute.
 * @program_name: argv[0] of main.
 * Return: 0 or 127 (command not found)
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
