#include "nickdun.h"

/**

 * add_node – include node to the beginning of list

 * @head: Location or address of the pr to the hd node

 * @str: the string of the field node

 * @num: the index to the node

 *

 * Return: List size

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

 * add_node_end – include node at the final part of list

 * @head: location/addresses ptr to the hd node

 * @str: the string of the node field

 * @num: the index of the node

 *

 * Return: List size

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

 * print_list_str – responsible for printing the string

 *   elements of list_t linked list

 * @h: first node the pointer to it

 *

 * Return: List size

 */

size_t print_list_str(const list_t *h)

{

	size_t w = 0;



	while (h)

	{

		_puts(h->str ? h->str : "(nil)");

		_puts("\n");

		h = h->next;

		w++;

	}

	return (w);

}



/**

 * delete_node_at_index – completely removes the node

 * @head: location of ptr to the node beginning

 * @index: node shown by the index

 *

 * Return: condition success 1 , else  0

 */

int delete_node_at_index(list_t **head, unsigned int index)

{

	list_t *node, *prev_node;

	unsigned int w = 0;



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

		if (w == index)

		{

			prev_node->next = node->next;

			free(node->str);

			free(node);

			return (1);

		}

		w++;

		prev_node = node;

		node = node->next;

	}

	return (0);

}



/**

 * free_list – release/freeing all the nodes

 * @head_ptr:  location of ptr to the hd of the node

 *

 * Return: void

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
