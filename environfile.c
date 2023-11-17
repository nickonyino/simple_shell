#include "nickdun.h"

/**

 * _mysetenv - Init var environment

 *  or adjust the current

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 *  Return: 0 if condition Success

 */

int _mysetenv(info_t *info)

{

	if (info->argc != 3)

	{

		_eputs("Invalid arg  numb \n");

		return (1);

	}

	if (_setenv(info, info->argv[1], info->argv[2]))

		return (0);

	return (1);

}



/**

 * _myenv – print currrent working environment

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 * Return: 0 if condition Success

 */

int _myenv(info_t *info)

{

	print_list_str(info->env);

	return (0);

}



/**

 * _getenv - get digit of environment variable

 * @info: Struct containig args

 * @name: environment variables naming convention

 *

 * Return: digits

 */

char *_getenv(info_t *info, const char *name)

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

 * _myunsetenv - delete variable environment

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 * Return: 0 if condition Success

 */

int _myunsetenv(info_t *info)

{

	int i;



	if (info->argc == 1)

	{

		_eputs(" very few args.\n");

		return (1);

	}

	for (i = 1; i <= info->argc; i++)

		_unsetenv(info, info->argv[i]);



	return (0);

}



/**

 * populate_env_list - increase linked list enironment

 * @info: Struct that holds  args for maintaining

 * constant funct prototype

 * Return: 0 if condition Success

 */

int populate_env_list(info_t *info)

{

	list_t *node = NULL;

	size_t i;



	for (i = 0; environ[i]; i++)

		add_node_end(&node, environ[i], 0);

	info->env = node;

	return (0);

}
