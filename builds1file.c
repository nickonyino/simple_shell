#include "nickdun.h"

/**

 * _mycd - changes current dir
 * @info: Struct that holds  args for maintaining
 * constant funct prototype.
 * Return:  0 if condition Success
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;
	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd fails text here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what is this? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');

		chdir_ret = /* TODO: what is this? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "unable to cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**

 * _myexit – leaves the shell

 * @info: Struct that holds  args for maintaining

 * constant funct prototype.

 * return: leaves with given exit conditions

 * (0) if info.argv[0] != "exit"

 */

int _myexit(info_t *info)

{
	int exitcheck;
	if (info->argv[1]) /* If is exit arg*/
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "unknown error: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**

 * _myhelp - changes current dir

 * @info: Struct that holds  args for maintaining

 * constant funct prototype.

 * Return:  0 if condition Success

 */

int _myhelp(info_t *info)

{
	char **arg_array;
	arg_array = info->argv;
	puts("help system call success. Funct yet to me implemented \n");
	if (0)
		_puts(*arg_array); /* temporary att_unused  */
	return (0);
}
