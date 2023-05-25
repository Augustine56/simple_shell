#include "shell.h"

/**
 * _err_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _err_atoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - This function prints an error message
 * @info: the parameter & return info struct
 * @e_str: string with targeted error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_c *info, char *e_str)
{
	_e_puts(info->fname);
	_e_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	_e_puts(": ");
	_e_puts(info->argv[0]);
	_e_puts(": ");
	_e_puts(e_str);
}

/**
 * print_d - This function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: num of chars printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _mis_, inst;

	if (fd == STDERR_FILENO)
		__putchar = _e_put_char;
	if (input < 0)
	{
		_mis_ = -input;
		__putchar('-');
		count++;
	}
	else
		_mis_ = input;
	inst = _mis_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_mis_ / i)
		{
			__putchar('0' + inst / i);
			count++;
		}
		inst %= i;
	}
	__putchar('0' + inst);
	count++;

	return (count);
}

/**
 * convert_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sym = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sym = '-';

	}
	array = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sym)
		*--ptr = sym;
	return (ptr);
}

/**
 * remove_comments - This function replaces first instance of '#' with '\0'
 * @buf: hex address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
