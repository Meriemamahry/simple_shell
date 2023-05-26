#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements
 *@arg: a string
 *@argv: an array
 *@path: a string
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error
 *@linecount_flag: if on count
 *@fname: the program filename
 *@env: linked list local
 *@environ: custom modified
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void ptu(char *);
int ptu_char(char);
int _fdt(char, int);
int _fds(char *, int);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *cpy(char *, char *, int);
char *_ncat(char *, char *, int);
char *str_chr(char *, char);

char **strtw(char *, char *);
char **strt2(char *, char);

char *_memo(char *, char, unsigned int);
void forfr(char **);
void *_realmadrid(void *, unsigned int, unsigned int);

int f_ree(void **);

int intera(info_t *);
int delim(char, char *);
int alpha(int);
int toint(char *);

int _errt(char *);
void printerr(info_t *, char *);
int printDec(int, int);
char *convnum(long int, int, int);
void remcomt(char *);

int _exiit(info_t *);
int change_dir(info_t *);
int _ch(info_t *);

int hist(info_t *);
int monAlias(info_t *);
int unsetAlias(info_t *, char *);
int setAlias(info_t *, char *);
int printAlias(list_t *);

ssize_t getIn(info_t *);
int _getline(info_t *, char **, size_t *);
void sigHandle(int);
ssize_t inbuf(info_t *, char **, size_t *);
ssize_t readbuf(info_t *, char *, size_t *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_getenviron(info_t *, const char *);
int _envm(info_t *);
int _mymoon(info_t *);
int _mydok(info_t *);
int envlist(info_t *);

char **envget(info_t *);
int _envntset(info_t *, char *);
int _weset(info_t *, char *, char *);

char *getHistory(info_t *);
int writeHistory(info_t *);
int readHistory(info_t *);
int buildHistory(info_t *, char *, int);
int renumberHistory(info_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t printList(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
