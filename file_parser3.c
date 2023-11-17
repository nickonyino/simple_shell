#include "nickdun.h"

/**

 * find_path – get cmd in str direction

 * @info: data Structure

 * @pathstr: Str direction

 * @cmd: command to get

 *

 * Return: if cmd direction found success else NULL

 */

char *find_path(info_t *info, char *pathstr, char *cmd)

{

	int y= 0, curr_pos = 0;

	char *path;



	if (!pathstr)

		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))

	{

		if (is_cmd(info, cmd))

			return (cmd);

	}

	while (1)

	{

		if (!pathstr[y] || pathstr[y] == ':')

		{

			path = dup_chars(pathstr, curr_pos, y);

			if (!*path)

				_strcat(path, cmd);

			else

			{

				_strcat(path, "/");

				_strcat(path, cmd);

			}

			if (is_cmd(info, path))

				return (path);

			if (!pathstr[y])

				break;

			curr_pos = y;

		}

		y++;

	}

	return (NULL);

}



/**

 * is_cmd – ascertains file is exe cmd

 * @info: data Structure

 * @path: direction file

 *

 * Return: 1 if condition success, 0 if else

 */

int is_cmd(info_t *info, char *path)

{

	struct stat st;



	(void)info;

	if (!path || stat(path, &st))

		return (0);



	if (st.st_mode & S_IFREG)

	{

		return (1);

	}

	return (0);

}



/**

 * dup_chars – replication char

 * @pathstr: direction path

 * @start: begins the Index

 * @stop: halt the index

 *

 * Return: the Buf to the new pointer address

 */

char *dup_chars(char *pathstr, int start, int stop)

{

	static char buf[1024];

	int y= 0, u = 0;



	for (u = 0, y = start; y< stop; y++)

		if (pathstr[y] != ':')

			buf[u++] = pathstr[y];

	buf[u] = 0;

	return (buf);

}
