#include "shell.h"

/**
 * my_exit - this function exits the shell
 * @info: Struct containing potential arguments
 *  Return: exits with exit status
 *         0 if info.argv[0] != "exit"
 */
int my_exit(info_c *info)
{
	int e_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		e_check = _err_atoi(info->argv[1]);
		if (e_check == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_e_puts(info->argv[1]);
			_e_put_char('\n');
			return (1);
		}
		info->err_num = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - this function changes the current dir of the process
 * @info: Struct containing arguments. 
 *  Return: Always 0
 */
int my_cd(info_c *info)
{
	char *s, *dir, buffer[1024];
	int ch_dir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			ch_dir = chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD=")), _putchar('\n');
		ch_dir = /* TODO: what should this be? */
			chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir = chdir(info->argv[1]);
	if (ch_dir == -1)
	{
		print_err(info, "can't cd to ");
		_e_puts(info->argv[1]), _e_put_char('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_c *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
