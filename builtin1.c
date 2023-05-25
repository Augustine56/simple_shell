#include "shell.h"

/**
 * _my_history - This function displays the history list
 * @info: Struct storing potential arguments.
 *  Return: Always 0
 */
int _my_history(info_c *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _unset_alias - This function sets alias to string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_c *info, char *str)
{
	char *p, c;
	int val;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	val = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (val);
}

/**
 * _set_alias - This function sets alias to string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_c *info, char *str)
{
	char *a_ptr;

	pa_ptr = _str_chr(str, '=');
	if (!a_ptr)
		return (1);
	if (!*++a_ptr)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - This function prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *a_ptr = NULL, *a = NULL;

	if (node)
	{
		a_ptr = _str_chr(node->str, '=');
		for (a = node->str; a <= a_ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(a_ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_alias(info_c *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _str_chr(info->argv[i], '=');
		if (ptr)
			_set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
