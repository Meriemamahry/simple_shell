#include "shell.h"

/**
 * _exiit - exits from shell
 * @p: Structure
 *  Return: exit status
 */
int _exiit(info_t *p)
{
int checks;

if (p->argv[1])
{
checks = _errt(p->argv[1]);
if (checks == -1)
{
p->status = 2;
printerr(p, "Illegal number: ");
ptu(p->argv[1]);
ptu_char('\n');
return (1);
}
p->err_num = _errt(p->argv[1]);
return (-2);
}
p->err_num = -1;
return (-2);
}

/**
 * change_dir - changes current dir
 * @i: Structure
 *  Return: 0
 */
int change_dir(info_t *i)
{
int ret;
char *s, *d;
char buffer[1024];

s= getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!i->argv[1])
{
d = _getenv(i, "HOME=");
if (!d)
ret =
chdir((d = _getenv(i, "PWD=")) ? d : "/");
else
ret = chdir(d);
}
else if (_strcmp(i->argv[1], "-") == 0)
{
if (!_getenv(i, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(i, "OLDPWD=")), _putchar('\n');
ret =
chdir((d = _getenv(i, "OLDPWD=")) ? d : "/");
}
else
ret = chdir(i->argv[1]);
if (ret == -1)
{
printerr(i, "can't cd to ");
ptu(i->argv[1]), ptu_char('\n');
}
else
{
_setenv(i, "OLDPWD", _getenv(i, "PWD="));
_setenv(i, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _ch - changes current dir
 * @i: Structure
 * Return: 0
 */
int _ch(info_t *i)
{
char **p;

p = i->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*p);
return (0);
}
