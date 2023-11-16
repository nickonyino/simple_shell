#include "nickdun.h" 

/** 

* print_list – the printing of linked list list_t 

* @h:  the next node ptr 

* 

* Return: range of list size 

*/ 

size_t print_list(const list_t *h) 

{ 

	size_t y = 0; 

  

	while (h) 

	{ 

		_puts(convert_number(h->num, 10, 0)); 

		_putchar(':'); 

		_putchar(' '); 

		_puts(h->str ? h->str : "(nil)"); 

		_puts("\n"); 

		h = h->next; 

		y++; 

	} 

	return (y); 

} 

  

/** 

* list_len – ascertain linked list length 

* @h: next node pointer 

* 

* Return:  range of size 

*/ 

size_t list_len(const list_t *h) 

{ 

	size_t y = 0; 

  

	while (h) 

	{ 

		h = h->next; 

		y++; 

	} 

	return (y); 

} 

  

/** 

* list_to_strings – replace arr of str of  list arow pointer to str 

* @head: next node ptr  

* 

* Return: the arr of str 

*/ 

char **list_to_strings(list_t *head) 

{ 

	list_t *node = head; 

	size_t y = list_len(head), x; 

	char **strs; 

	char *str; 

  

	if (!head || !y) 

		return (NULL); 

	strs = malloc(sizeof(char *) * (y + 1)); 

	if (!strs) 

		return (NULL); 

	for (y = 0; node; node = node->next, y++) 

	{ 

		str = malloc(_strlen(node->str) + 1); 

		if (!str) 

		{ 

			for (x = 0; x < y; x++) 

				free(strs[x]); 

			free(strs); 

			return (NULL); 

		} 

  

		str = _strcpy(str, node->str); 

		strs[y] = str; 

	} 

	strs[y] = NULL; 

	return (strs); 

} 

  

 /** 

* get_node_index – find node indexed 

* @head: the listed head ptr 

* @node: the node ptr 

* 

* Return: -1 or node indexed 

*/ 

ssize_t get_node_index(list_t *head, list_t *node) 

{ 

	size_t y = 0; 

  

	while (head) 

	{ 

		if (head == node) 

			return (y); 

		head = head->next; 

		y++; 

	} 

	return (-1); 

} 

 

  

/** 

* node_starts_with - restores nodes prefix 

* @node: the listed head ptr  

* @prefix: the equal string 

* @c: the following char after prefix equals 

* 

* Return: NULL or equal node 

*/ 

list_t *node_starts_with(list_t *node, char *prefix, char c) 

{ 

	char *p = NULL; 

  

	while (node) 

	{ 

		p = starts_with(node->str, prefix); 

		if (p && ((c == -1) || (*p == c))) 

			return (node); 

		node = node->next; 

	} 

	return (NULL); 

} 
