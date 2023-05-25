#include "shell.h"

/**
 * is_interactive - this function returns true if shell is in interactive mode
 * @info: struct pointer
 *
 * Return: if in interactive mode returns 1, otherwise returns 0
 */
int interactive(info_c *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - this function checks to see if given character is a delimeter
 * @c: character
 * @delim: delimeter string
 * Return: if true return 1, if false 0
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_is_alpha - this function checks for alphabetic character
 *@c: inputed character
 *Return: if c is alphabetic returns 1, otherwise 0
 */

int _is_alpha(int c)
{
	if ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *a_to_i - this function converts string to an integer
 *@s: the string to be converted to integer
 *Return: if no numbers in string returns 0, otherwise returns the converted integer
 */

int a_to_i(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
