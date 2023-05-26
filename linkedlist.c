#include "shell.h"

/**
 * add_alias_to_end - Adds a node to the end of a alias_t linked list.
 * @head_ptr: A pointer to the head_ptr of the list_t list.
 * @alias_name: The alias_name of the new alias to be added.
 * @alias_value: The alias_value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_to_end(alias_t **head_ptr, char *alias_name, char *alias_value)
{
	alias_t *node_new = malloc(sizeof(alias_t));
	alias_t *node_last;

	if (!node_new)
		return (NULL);

	node_new->next = NULL;
	node_new->alias_name = malloc(sizeof(char) * (_strlen(alias_name) + 1));
	if (!node_new->alias_name)
	{
		free(node_new);
		return (NULL);
	}
	node_new->alias_value = alias_value;
	_strcpy(node_new->alias_name, alias_name);

	if (*head_ptr)
	{
		node_last = *head_ptr;
		while (node_last->next != NULL)
			node_last = node_last->next;
		node_last->next = node_new;
	}
	else
		*head_ptr = node_new;

	return (node_new);
}

/**
 * add_node_to_end - Adds a node to the end of  linked list.
 * @head_ptr: A pointer to the head_ptr of the list_t list.
 * @dir_path: The directoryectory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_to_end(list_t **head_ptr, char *dir_path)
{
	list_t *node_new = malloc(sizeof(list_t));
	list_t *node_last;

	if (!node_new)
		return (NULL);

	node_new->dir_path = dir_path;
	node_new->next = NULL;

	if (*head_ptr)
	{
		node_last = *head_ptr;
		while (node_last->next != NULL)
			node_last = node_last->next;
		node_last->next = node_new;
	}
	else
		*head_ptr = node_new;

	return (node_new);
}

/**
 * frees_alias_list - Frees alias_t linked list.
 * @head_ptr: THe head_ptr of the alias_t list.
 */
void frees_alias_list(alias_t *head_ptr)
{
	alias_t *next;

	while (head_ptr)
	{
		next = head_ptr->next;
		free(head_ptr->alias_name);
		free(head_ptr->alias_value);
		free(head_ptr);
		head_ptr = next;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head_ptr: The head_ptr of the list_t list.
 */
void free_list(list_t *head_ptr)
{
	list_t *next;

	while (head_ptr)
	{
		next = head_ptr->next;
		free(head_ptr->dir_path);
		free(head_ptr);
		head_ptr = next;
	}
}
