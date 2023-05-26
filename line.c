#include "shell.h"

/**
 * inbuf - buffer
 * @i: structure
 * @b: address of i
 * @len: address of len
 * Return: read
 */
ssize_t inbuf(info_t *i, char **b, size_t *len)
{
	ssize_t s = 0;
	size_t p = 0;

	if (!*len)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sigHandle);
#if USE_GETLINE
		s = getline(b, &p, stdin);
#else
		s = _getline(i, b, &p);
#endif
		if (s > 0)
		{
			if ((*b)[s - 1] == '\n')
			{
				(*b)[s - 1] = '\0';
				s--;
			}
			i->linecount_flag = 1;
			remcomt(*b);
			buildHistory(i, *b, i->histcount++);
			{
				*len = s;
				i->cmd_buf = b;
			}
		}
	}
	return (s);
}

/**
 * getIn - line - the newline
 * @i: structure
 * Return: bytes read
 */
ssize_t getIn(info_t *i)
{
	static char *b;
	static size_t t, j, l;
	ssize_t r = 0;
	char **k = &(i->arg), *p;

	_putchar(BUF_FLUSH);
	r = inbuf(i, &b, &l);
	if (r == -1) /* EOF */
		return (-1);
	if (l)
	{
		j = t;
		p = b + t;

		check_chain(i, b, &j, t, l);
		while (j < l)
		{
			if (washchaine(i, b, &j))
				break;
			j++;
		}

		t = j + 1;
		if (t >= l)
		{
			t = l = 0;
			i->cmd_buf_type = CMD_NORM;
		}

		*k = p;
		return (_strlen(p));
	}

	*k = b;
	return (r);
}

/**
 * readbuf - reads a buffer
 * @i: structure
 * @b: buffer
 * @s: size
 * Return: list
 */
ssize_t readbuf(info_t *i, char *b, size_t *s)
{
	ssize_t p = 0;

	if (*s)
		return (0);
	p = read(i->readfd, b, READ_BUF_SIZE);
	if (p >= 0)
		*s = p;
	return (p);
}

/**
 * _getline - gets the next line
 * @f: structure
 * @a: address of pointer to buffer, preallocated or NULL
 * @l: size
 * Return: an int
 */
int _getline(info_t *f, char **a, size_t *l)
{
	char *p = NULL, *t = NULL, *c;
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;

	p = *a;
	if (p && l)
		s = *l;
	if (i == len)
		i = len = 0;

	r = readbuf(f, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	t = _realmadrid(p, s, s ? s + k : k + 1);
	if (!t)
		return (p ? free(p), -1 : -1);

	if (s)
		_ncat(t, buf + i, k - i);
	else
		cpy(t, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = t;

	if (l)
		*l = s;
	*a = p;
	return (s);
}

/**
 * sigHandle - stops ctrl+c
 * @sig: signal
 */
void sigHandle(__attribute__((unused))int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
