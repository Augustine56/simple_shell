#include "shell.h"

/**
 * **strtow - splits a string into words. duplicate delimiters ignored
 * @str: input str
 * @d: delimeter str
 * Return: a pointer
 */

char **strtow(char *str, char *d)
{
	int index, j, k, m, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (index = 0; str[index] != '\0'; index++)
		if (!is_delim(str[index], d) && (is_delim(str[index + 1], d) || !str[index + 1]))
			n_words++;

	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = 0, j = 0; j < n_words; j++)
	{
		while (is_delim(str[index], d))
			index++;
		k = 0;
		while (!is_delim(str[index + k], d) && str[index + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - This function splits a string into words
 * @str: input string
 * @d: delimeter
 * Return: a pointer
 */
char **strtow2(char *str, char d)
{
	int index, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (index = 0; str[index] != '\0'; index++)
		if ((str[i] != d && str[index + 1] == d) ||
		    (str[i] != d && !str[index + 1]) || str[index + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = 0, j = 0; j < numwords; j++)
	{
		while (str[index] == d && str[i] != d)
			index++;
		k = 0;
		while (str[index + k] != d && str[index + k] && str[index + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
