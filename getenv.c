#include "shell.h"

/**
 * get_envir - This function returns the string array copy of our environ
 * @info: Struct storing potential arguments.
 * Return: Always 0
 */
char **get_envir(info_c *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unset_env - THis function removes an environment variable
 * @info: Struct containing potential arguments.
 *  Return: delete return 1, 0 otherwise
 * @var: the string env var property
 */
int _unset_env(info_c *info, char *var)
{
	list_t *node_ptr = info->env;
	size_t i = 0;
	char *p;

	if (!node_ptr || !var)
		return (0);

	while (node_ptr)
	{
		p = starts_with(node_ptr->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node_ptr = info->env;
			continue;
		}
		node_ptr = node_ptr->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_c *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node_ptr;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node_ptr = info->env;
	while (node_ptr)
	{
		p = starts_with(node_ptr->str, var);
		if (p && *p == '=')
		{
			free(node_ptr->str);
			node_ptr->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node_ptr = node_ptr->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
