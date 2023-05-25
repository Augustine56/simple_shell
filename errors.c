#include "shell.h"

/**
 *_e_puts - This function prints an input string
 * @str: string
 *
 * Return: void
 */
void _e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_e_put_char(str[i]);
		i++;
	}
}

/**
 * _e_put_char - This function prints the character c to stderr
 * @c: character
 *
 * Return: On success 1, -1 is returned, and errno is set appropriately
 */
int _e_put_char(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _put_fd - This function writes the character c to given fd
 * @c: character
 * @fd: The file descriptor to write into
 *
 * Return: On success 1, -1 is returned, and errno is set appropriately.
 */
int _put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_puts_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _put_fd(*str++, fd);
	}
	return (i);
}
