#include "shell.h"

/**
 * is_cmd - This function determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat stf;

	(void)info;
	if (!path || stat(path, &stf))
		return (0);

	if (stf.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_char - This function duplicates characters
 * @pathstr: the PATH string
 * @start: start index
 * @stop: end index
 *
 * Return: pointer to new buffer
 */
char *dup_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _find_path - This function finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_ind = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strl(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			p = dup_char(pathstr, curr_ind, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[i])
				break;
			curr_ind = i;
		}
		i++;
	}
	return (NULL);
}
