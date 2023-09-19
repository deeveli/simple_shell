#include "shell.h"
/**
 * exit_shell - Exits the shell.
 * @info: Pointer to the info_t structure containing arguments.
 *
 * Return: Exits with a given exit status or 0 if info->argv[0] != "exit".
 */
int exit_shell(info_t *info)
{
	int exit_code;

	if (info->argv[1]) /* Check if there is an exit argument */
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_code;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * change_directory - Changes the current directory of the process.
 * @info: Pointer to the info_t structure containing arguments.
 *
 * Return: Always 0.
 */
int change_directory(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_re;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_re = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_re = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_re = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_re = chdir(info->argv[1]);
	if (chdir_re == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * show_help - Displays help information.
 * @info: Pointer to the info_t structure containing arguments.
 *
 * Return: Always 0.
 */
int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help: Functionality not yet implemented\n");
	if (0)
		_puts(*arg_array); /* Temporary unused workaround */
	return (0);
}
