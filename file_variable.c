#include "nickdun.h"
/**
 * is_chain -checks and test  current character 
 * buffer if it is chain delimeter
 * @info:  Parameter or arguement Structure
 * @buf: the Character of the  Buffer
 * @p: Location or addresses of the buf
 *
 * Return: 1 on successs, 0 if not
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') /* found end  command */
	{
		buf[x] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * check_chain - loking and re-checking the point of entry
 * @info: arguement or proposed parameter Struct
 * @buf: the character buffer to check
 * @p: location of current position or address
 * @i:beginning or the origi buff position
 * @len:  lenght of the buffer checked
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * replace_alias - change/replaces the proposed aliases
 * @info:  arguement/ the parameter Structure
 *
 * Return: after being replaced return 1, else return 0
 */
int replace_alias(info_t *info)
{
	int w;
	list_t *node;
	char *p;

	for (w = 0; w < 10; w++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
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
 * replace_vars -change/ replaces the proposed variable
 * @info: Parguement/parameterused in the  Structure
 *
 * Return: after being changed/replaced 1, else return 0
 */
int replace_vars(info_t *info)
{
	int w = 0;
	list_t *node;

	for (w = 0; info->argv[w]; w++)
	{
		if (info->argv[w][0] != '$' || !info->argv[w][1])
			continue;

		if (!_strcmp(info->argv[w], "$?"))
		{
			replace_string(&(info->argv[w]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[w], "$$"))
		{
			replace_string(&(info->argv[w]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[w][1], '=');
		if (node)
		{
			replace_string(&(info->argv[w]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[w], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - changes/replacs the proposed String
 * @old: Location or  possible address of the old string
 * @new: the new string being used
 *
 * Return: being replaced 1, else return 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
