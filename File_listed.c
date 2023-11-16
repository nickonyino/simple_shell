#include "nickdun.h" 

 

/** 

* add_node_end - Appends to end of list, node 

* @head: location of ptr to head of the node 

* @str: data type string node field 

* @num: index of node 

* 

* Return: range of list size 

*/ 

list_t *add_node_end(list_t **head, const char *str, int num) 

{ 

	list_t *new_node, *node; 

  

	if (!head) 

		return (NULL); 

  

	node = *head; 

	new_node = malloc(sizeof(list_t)); 

	if (!new_node) 

		return (NULL); 

	_memset((void *)new_node, 0, sizeof(list_t)); 

	new_node->num = num; 

	if (str) 

	{ 

		new_node->str = _strdup(str); 

		if (!new_node->str) 

		{ 

			free(new_node); 

			return (NULL); 

		} 

	} 

	if (node) 

	{ 

		while (node->next) 

			node = node->next; 

		node->next = new_node; 

	} 

	else 

		*head = new_node; 

	return (new_node); 

} 

 

/** 

* add_node – append node at the beginning of list 

* @head: ptr location to head node 

* @str: data type String node field 

* @num: index of node 

* 

* Return: range of list size 

*/ 

list_t *add_node(list_t **head, const char *str, int num) 

{ 

	list_t *new_head; 

  

	if (!head) 

		return (NULL); 

	new_head = malloc(sizeof(list_t)); 

	if (!new_head) 

		return (NULL); 

	_memset((void *)new_head, 0, sizeof(list_t)); 

	new_head->num = num; 

	if (str) 

	{ 

		new_head->str = _strdup(str); 

		if (!new_head->str) 

		{ 

			free(new_head); 

			return (NULL); 

		} 

	} 

	new_head->next = *head; 

	*head = new_head; 

	return (new_head); 

} 

   

/** 

* print_list_str – Printing of string of a linked list list_t 

* @h:  start node ptr 

* 

* Return: range of list size 

*/ 

size_t print_list_str(const list_t *h) 

{ 

	size_t y = 0; 

  

	while (h) 

	{ 

		_puts(h->str ? h->str : "(nil)"); 

		_puts("\n"); 

		h = h->next; 

		y++; 

	} 

	return (y); 

} 

/** 

* free_list - releases nodes 

* @head_ptr: head node location of ptr 

* 

* Return:  is void 

*/ 

void free_list(list_t **head_ptr) 

{ 

	list_t *node, *next_node, *head; 

  

	if (!head_ptr || !*head_ptr) 

		return; 

	head = *head_ptr; 

	node = head; 

	while (node) 

	{ 

		next_node = node->next; 

		free(node->str); 

		free(node); 

		node = next_node; 

	} 

	*head_ptr = NULL; 

} 

 

  

/** 

* delete_node_at_index – rm node 

* @head: start node location ptr 

* @index: the Indexed node 

* 

* Return: 1 if condition Success ,  0 if otherwise 

*/ 

int delete_node_at_index(list_t **head, unsigned int index) 

{ 

	list_t *node, *prev_node; 

	unsigned int y = 0; 

  

	if (!head || !*head) 

		return (0); 

  

	if (!index) 

	{ 

		node = *head; 

		*head = (*head)->next; 

		free(node->str); 

		free(node); 

		return (1); 

	} 

	node = *head; 

	while (node) 

	{ 

		if (y == index) 

		{ 

			prev_node->next = node->next; 

			free(node->str); 

			free(node); 
