#include "shell.h"

/**
 * add_new_node - This function adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - This function adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}

/**
 * print_list_str - This function prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - This function deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node_ptr, *prev_node_ptr;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node_ptr = *head;
		*head = (*head)->next;
		free(node_ptr->str);
		free(node_ptr);
		return (1);
	}
	node_ptr = *head;
	while (node_ptr)
	{
		if (i == index)
		{
			prev_node_ptr->next = node_ptr->next;
			free(node_ptr->str);
			free(node_ptr);
			return (1);
		}
		i++;
		prev_node_ptr = node_ptr;
		node_ptr = node_ptr->next;
	}
	return (0);
}

/**
 * free_list - This function frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: nothing
 */
void free_list(list_t **head_ptr)
{
	list_t *node_ptr, *next_node_ptr, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node_ptr = head;
	while (node_ptr)
	{
		next_node_ptr = node_ptr->next;
		free(node_ptr->str);
		free(node_ptr);
		node_ptr = next_node_ptr;
	}
	*head_ptr = NULL;
}
