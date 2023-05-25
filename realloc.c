#include "shell.h"

/**
 **_memset - This function fills memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * ffree - This function frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **l = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(l);
}

/**
 * _reallocd - This function reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of a given previous block
 * @new_size: byte size of a given new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocd(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pr = malloc(new_size);
	if (!pr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pr);
}
