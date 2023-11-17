#include "nickdun.h"

/**

 * _unsetenv - delete variable environment

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 *  Return: 1 if delete success , if otherwise 0

 * @var: variable property str environment

 */

int _unsetenv(info_t *info, char *var)

{

	list_t *node = info->env;

	size_t i = 0;

	char *p;



	if (!node || !var)

		return (0);



	while (node)

	{

		p = starts_with(node->str, var);

		if (p && *p == '=')

		{

			info->env_changed = delete_node_at_index(&(info->env), i);

			i = 0;

			node = info->env;

			continue;

		}

		node = node->next;

		i++;

	}

	return (info->env_changed);

}





/**

 * get_environ - restore str arr copy of the environment

 * @info Struct that holds  args for maintaining

 * constant funct prototype

 * Return:  0 if condition Success

 */



char **get_environ(info_t *info)

{

	if (!info->environ || info->env_changed)

	{

		info->environ = list_to_strings(info->env);

		info->env_changed = 0;

	}



	return (info->environ);

}





/**

 * _setenv - begin new variable environment,

 *             or adjust the one that exists

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 * @var: variable property str environment

 * @value: status of variable str environment

 *  Return:  0 if condition Success

 */

int _setenv(info_t *info, char *var, char *value)

{

	char *buf = NULL;

	list_t *node;

	char *p;



	if (!var || !value)

		return (0);



	buf = malloc(_strlen(var) + _strlen(value) + 2);

	if (!buf)

		return (1);

	_strcpy(buf, var);

	_strcat(buf, "=");

	_strcat(buf, value);

	node = info->env;

	while (node)

	{

		p = starts_with(node->str, var);

		if (p && *p == '=')

		{

			free(node->str);

			node->str = buf;

			info->env_changed = 1;

			return (0);

		}

		node = node->next;

	}

	add_node_end(&(info->env), buf, 0);

	free(buf);

	info->env_changed = 1;

	return (0);

}



/**

 * set_info – begin structure info_t.

 * @info: location of structure.

 * @av: the vector parameter.

 */

void set_info(info_t *info, char **av)

{

	int z = 0;



	info->fname = av[0];

	if (info->arg)

	{

		info->argv = strtow(info->arg, " \t");

		if (!info->argv)

		{

			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)

			{

				info->argv[0] = _strdup(info->arg);

				info->argv[1] = NULL;

			}

		}

		for (z = 0; info->argv && info->argv[z]; z++)

			;

		info->argc = z;



		replace_alias(info);

		replace_vars(info);

	}

}





/**

 * clear_info - begin structure info_t.

 * @info: location of structure.

 */

void clear_info(info_t *info)

{

	info->arg = NULL;

	info->argv = NULL;

	info->path = NULL;

	info->argc = 0;

}





/**

 * free_info – Release structure info_t field

 * @info: location of structure.

 * @all: releasing of info_t in all fileds

 */

void free_info(info_t *info, int all)

{

	ffree(info->argv);

	info->argv = NULL;

	info->path = NULL;

	if (all)

	{

		if (!info->cmd_buf)

			free(info->arg);

		if (info->env)

			free_list(&(info->env));

		if (info->history)

			free_list(&(info->history));

		if (info->alias)

			free_list(&(info->alias));

		ffree(info->environ);

		info->environ = NULL;

		bfree((void **)info->cmd_buf);

		if (info->readfd > 2)

			close(info->readfd);

		_putchar(BUF_FLUSH);

	}

}
