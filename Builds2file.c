Builds2file.c 

#include "Nickdun.h" 

/** 

* unset_alias - set alias to  str 

* @info: arg structure 

* @str: str alias 

* Return: 0 if condition Success, 1 if error 

*/ 

int unset_alias(info_t *info, char *str) 

{ 

	char *p, d; 

	int ret; 

  

	p = _strchr(str, '='); 

	if (!p) 

		return (1); 

	d = *p; 

	*p = 0; 

	ret = delete_node_at_index(&(info->alias), 

		get_node_index(info->alias, node_starts_with(info->alias, str, -1))); 

	*p = d; 

	return (ret); 

} 

 

 

/** 

* _myhistory - shows history list, one commands by line, preceds 

*              line numb, starts  0. 

* @info: Struct that holds  args for maintaining 

* constant funct prototype 

*  Return:  0 if condtion Success 

*/ 

int _myhistory(info_t *info) 

{ 

	print_list(info->history); 

	return (0); 

} 

  

  

/** 

* set_alias - set alias to  str 

* @info: arg structure 

* @str: str alias 

* 

* Return: 0 if condition success, 1 if error 

*/ 

int set_alias(info_t *info, char *str) 

{ 

	char *p; 

  

	p = _strchr(str, '='); 

	if (!p) 

		return (1); 

	if (!*++p) 

		return (unset_alias(info, str)); 

  

	unset_alias(info, str); 

	return (add_node_end(&(info->alias), str, 0) == NULL); 

} 

  

/** 

* print_alias - print alias to str 

* @node: alias node 

* 

* return: 0 if condition Success, 1 if error 

*/ 

int print_alias(list_t *node) 

{ 

	char *p = NULL, *b = NULL; 

  

	if (node) 

	{ 

		p = _strchr(node->str, '='); 

		for (b = node->str; b <= p; b++) 

		_putchar(*b); 

		_putchar('\''); 

		_puts(p + 1); 

		_puts("'\n"); 

		return (0); 

	} 

	return (1); 

} 

  

/** 

* _myalias – acts as alias built-in 

* @info: Struct that holds  args for maintaining 

* constant funct prototype 

 *  Return:  0 if condition Success 

*/ 

int _myalias(info_t *info) 

{ 

	int i = 0; 

	char *p = NULL; 

	list_t *node = NULL; 

  

	if (info->argc == 1) 

	{ 

		node = info->alias; 

		while (node) 

		{ 

			print_alias(node); 

			node = node->next; 

		} 

		return (0); 

	} 

	for (i = 1; info->argv[i]; i++) 

	{ 

		p = _strchr(info->argv[i], '='); 

		if (p) 

			set_alias(info, info->argv[i]); 

		else 

			print_alias(node_starts_with(info->alias, info->argv[i], '=')); 

	} 

  

	return (0); 

} 
