#include "shell.h"

/**
 * _strcpy - This function copies a string
 * @dest: the destination address
 * @src: the source address
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * _strdup - This function duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *reti;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	reti = malloc(sizeof(char) * (l + 1));
	if (!reti)
		return (NULL);
	for (l++; l--;)
		reti[l] = *--str;
	return (reti);
}

/**
 *_puts - This function prints an input string
 *@str: string to be printed
 *
 * Return: void
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - This function writes the character c to stdout
 * @c: char to print
 *
 * Return: On success 1, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}
