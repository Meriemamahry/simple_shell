#include "shell.h"

/**
 * ajouternoeud - adds a node t
 * @heado: address of pointer te
 * @str: str field of node
 * @num: node index used by history
 * Return: size
 */
list_t *ajouternoeud(list_t **heado, const char *str, int num)
{
list_t *new_headop;

if (!heado)
return (NULL);
new_headop = malloc(sizeof(list_t));
if (!new_headop)
return (NULL);
_memo((void *)new_headop, 0, sizeof(list_t));
new_headop->num = num;
if (str)
{
new_headop->str = _strdup(str);
if (!new_headop->str)
{
free(new_headop);
return (NULL);
}
}
new_headop->next = *heado;
*heado = new_headop;
return (new_headop);
}

/**
 * ajouter_fin - adds a node to the end of the list
 * @heado: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *ajouter_fin(list_t **heado, const char *str, int num)
{
list_t *new_nodetqwd, *nodetqwd;

if (!heado)
return (NULL);

nodetqwd = *heado;
new_nodetqwd = malloc(sizeof(list_t));
if (!new_nodetqwd)
return (NULL);
_memo((void *)new_nodetqwd, 0, sizeof(list_t));
new_nodetqwd->num = num;
if (str)
{
new_nodetqwd->str = _strdup(str);
if (!new_nodetqwd->str)
{
free(new_nodetqwd);
return (NULL);
}
}
if (nodetqwd)
{
while (nodetqwd->next)
nodetqwd = nodetqwd->next;
nodetqwd->next = new_nodetqwd;
}
else
*heado = new_nodetqwd;
return (new_nodetqwd);
}

/**
 * printlist - prints only the
 * @hop: pointer to first node
 * Return: size of list
 */
size_t printlist(const list_t *hop)
{
size_t i = 0;

while (hop)
{
_puts(hop->str ? hop->str : "(nil)");
_puts("\n");
hop = hop->next;
i++;
}
return (i);
}

/**
 * supprimerlist - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int supprimerlist(list_t **headop, unsigned int index)
{
list_t *nodetqwd, *next_nodetqwd;
unsigned int i = 0;

if (!headop || !*headop)
return (0);
if (!index)
{
nodetqwd = *headop;
*headop = (*headop)->next;
free(nodetqwd->str);
free(nodetqwd);
return (1);
}
nodetqwd = *headop;
while (nodetqwd)
{
if (i == index)
{
next_nodetqwd->next = nodetqwd->next;
free(nodetqwd->str);
free(nodetqwd);
return (1);
}
i++;
next_nodetqwd = nodetqwd;
nodetqwd = nodetqwd->next;
}
return (0);
}

/**
 * freelist - frees all nodes of a list
 * @headop: address of pointer to head node
 *
 * Return: void
 */
void freelist(list_t **headop)
{
list_t *nodetqwd, *next_nodetqwd, *head;

if (!headop || !*headop)
return;
head = *headop;
nodetqwd = head;
while (nodetqwd)
{
next_nodetqwd = nodetqwd->next;
free(nodetqwd->str);
free(nodetqwd);
nodetqwd = next_nodetqwd;
}
*headop = NULL;
}
