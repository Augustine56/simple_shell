#include "shell.h"

/**
 * _get_hist_file - This function gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *_get_hist_file(info_t *info)
{
	char *buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strl(dir) + _strl(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_hist - This function creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filen = _get_hist_file(info);
	list_t *node = NULL;

	if (!filen)
		return (-1);

	fd = open(filen, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filen);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - This reads history from file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, f_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = _get_hist_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, f_size);
	buffer[f_size] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < f_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_hist_list(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - This function adds entry to a history linked list
 * @info: Struct storing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node_ptr = NULL;

	if (info->history)
		node_ptr = info->history;
	add_node_end(&node_ptr, buf, linecount);

	if (!info->history)
		info->history = node_ptr;
	return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @info: Struct storing potential arguments.
 *
 * Return: the newest histcount
 */
int renumber_hist(info_t *info)
{
	list_t *node_ptr = info->history;
	int i = 0;

	while (node_ptr)
	{
		node_ptr->num = i++;
		node_ptr = node_ptr->next;
	}
	return (info->histcount = i);
}
