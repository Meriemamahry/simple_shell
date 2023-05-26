#include "shell.h"

/**
 **_memo - byte byte byte
 *@po: the pointer
 *@byt_e: the byte
 *@n:bytes to be filled
 *Return: pointer
 */
char *_memo(char *po, char byt_e, unsigned int n)
{
unsigned int k;

for (k = 0; k < n; k++)
po[k] = byt_e;
return (po);
}

/**
 * forfr - frees a string of strings
 * @pop: string of strings
 */
void forfr(char **pop)
{
char **a = pop;

if (!pop)
return;
while (*pop)
free(*pop++);
free(a);
}

/**
 * _realmadrid - reallocates
 * @potr: pointer to pre
 * @old_si: byte size
 * @new_si: byte size
 * Return: pointer
 */
void *_realmadrid(void *potr, unsigned int old_si, unsigned int new_si)
{
char *po;

if (!potr)
return (malloc(new_si));
if (!new_si)
return (free(potr), NULL);
if (new_si == old_si)
return (potr);
po = malloc(new_si);
if (!po)
return (NULL);
old_si = old_si < new_si ? old_si : new_si;
while (old_si--)
po[old_si] = ((char *)potr)[old_si];
free(potr);
return (po);
}
