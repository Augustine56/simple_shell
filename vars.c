#include "shell.h"

/**
 * is_chain - This functions test if current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t sz = *p;

	if (buf[sz] == '|' && buf[sz + 1] == '|')
	{
		buf[sz] = 0;
		sz++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[sz] == '&' && buf[sz + 1] == '&')
	{
		buf[sz] = 0;
		sz++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[sz] == ';') /* found end of this command */
	{
		buf[sz] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = sz;
	return (1);
}

/**
 * check_chain - This function checks we should continue chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: nothing
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jl = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			jl = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			jl = len;
		}
	}

	*p = jl;
}

/**
 * rep_alias - This function replaces an aliases in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
	int index;
	list_t *node_ptr;
	char *p;

	for (index = 0; index < 10; index++)
	{
		node_ptr = node_starts_with(info->alias, info->argv[0], '=');
		if (!node_ptr)
			return (0);
		free(info->argv[0]);
		p = _strchr(node_ptr->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_vars - This replaces vars in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
	int index = 0;
	list_t *node_ptr;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			rep_string(&(info->argv[index]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			rep_string(&(info->argv[index]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node_ptr = node_starts_with(info->env, &info->argv[index][1], '=');
		if (node_ptr)
		{
			rep_string(&(info->argv[index]),
				_strdup(_strchr(node_ptr->str, '=') + 1));
			continue;
		}
		rep_string(&info->argv[index], _strdup(""));

	}
	return (0);
}

/**
 * rep_string - This function replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
