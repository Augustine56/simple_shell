#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_c *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(info_c *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set_env - This function initializes a new environment variable,
 *             or modify an existing one
 * @info: Struct storing potential arguments.
 *  Return: Always 0
 */
int my_set_env(info_c *info)
{
	if (info->argc != 3)
	{
		_e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - This function removes an environment variable
 * @info: Struct storing potential arguments.
 *  Return: Always 0
 */
int my_unset_env(info_c *info)
{
	int i;

	if (info->argc == 1)
	{
		_e_puts("Arguements too few.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - This function populates env linked list
 * @info: Struct storing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_c *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
