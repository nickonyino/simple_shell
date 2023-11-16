#include "nickdun.h" 

/** 

* replace_string - change str 

* @old: old str location 

* @new: unused str 

* 

* Return: changed 1 if condition success, otherwise 0 

*/ 

int replace_string(char **old, char *new) 

{ 

	free(*old); 

	*old = new; 

	return (1); 

} 

/** 

* is_chain – find out if current char is a chain delim 

* @info:  args structure 

* @buf: the Buffer char 

* @p: location of buffer 

* 

* Return: 1 if condition Success, 0  if otherwise 

*/ 

int is_chain(info_t *info, char *buf, size_t *p) 

{ 

	size_t x = *p; 

  

	if (buf[x] == '|' && buf[x + 1] == '|') 

	{ 

		buf[x] = 0; 

		x++; 

		info -> cmd_buf_type = CMD_OR; 

	} 

	else if (buf[x] == '&' && buf[x + 1] == '&') 

	{ 

		buf[x] = 0; 

		x++; 

		info -> cmd_buf_type = CMD_AND; 

	} 

	else if (buf[x] == ';') /* got end  cmd */ 

	{ 

		buf[x] = 0; 

		info -> cmd_buf_type = CMD_CHAIN; 

	} 

	else 

		return (0); 

	*p = x; 

	return (1); 

} 

   

/** 

* replace_alias – change aliases 

* @info:  args structure 

* 

* Return: 1 if changed success, otherwise 0 

*/ 

int replace_alias(info_t *info) 

{ 

	int y; 

	list_t *node; 

	char *p; 

  

	for (y = 0; y < 10; y++) 

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

* replace_vars – change varible 

* @info: args structure 

* 

* Return:  1 if condition success, otherwise 0 

*/ 

int replace_vars(info_t *info) 

{ 

	int y = 0; 

	list_t *node; 

  

	for (y = 0; info->argv[y]; y++) 

	{ 

		if (info->argv[y][0] != '$' || !info->argv[y][1]) 

			continue; 

  

			if (!_strcmp(info->argv[y], "$?")) 

		{ 

			replace_string(&(info->argv[y]), 

					_strdup(convert_number(info->status, 10, 0))); 

			continue; 

		} 

		if (!_strcmp(info->argv[y], "$$")) 

		{ 

			replace_string(&(info->argv[y]), 

					_strdup(convert_number(getpid(), 10, 0))); 

			continue; 

		} 

		node = node_starts_with(info->env, &info->argv[y][1], '='); 

		if (node) 

		{ 

			replace_string(&(info->argv[y]), 

					_strdup(_strchr(node->str, '=') + 1)); 

			continue; 

		} 

		replace_string(&info->argv[y], _strdup("")); 

  

	} 

	return (0); 

} 

/** 

* check_chain – looks at entry point 

* @info: args structure 

* @buf: the char buffer 

* @p: buffer location 

* @i: begin buff area 

* @len: the buff len 

* 

* Return: Void 

*/ 

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len) 

{ 

	size_t x = *p; 

  

	if (info -> cmd_buf_type == CMD_AND) 

	{ 

		if (info->status) 

		{ 

			buf[i] = 0; 

			x = len; 

		} 

	} 

	if (info -> cmd_buf_type == CMD_OR) 

	{ 

		if (!info->status) 

		{ 

			buf[i] = 0; 

			x = len; 

		} 

	} 

  

	*p = x; 

} 
