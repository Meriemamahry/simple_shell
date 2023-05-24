#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure 
 *  Return: 0 if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = _erratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @info: Structure
 *  Return: 0
 */
int _mycd(info_t *info)
{
	int i;
	char *s, *d, buffer[1024];
	
	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		d = _getenv(info, "HOME=");
		if (!d)
			i = /* TODO: what should this be? */
				chdir((d = _getenv(info, "PWD=")) ? d : "/");
		else
			i = chdir(d);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		i = /* TODO: what should this be? */
			chdir((d = _getenv(info, "OLDPWD=")) ? d : "/");
	}
	else
		i = chdir(info->argv[1]);
	if (i == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory
 * @info: Structure
 *  Return: 0
 */
int _myhelp(info_t *info)
{
	char **a;

	a = info->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*a);
	return (0);
}
