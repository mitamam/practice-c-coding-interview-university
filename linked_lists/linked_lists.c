#include "linked_lists.h"

t_list *list_new(void)
{
	t_list *newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->head = NULL;
	newlist->tail = NULL;
	newlist->size = 0;
	return (newlist);
}

void list_destroy(t_list *list)
{
	t_listnode *node;
	t_listnode *next;

	if (!list)
		return ;
	node = list->head;
	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
	free(list);
}

t_listnode *listnode_new(const int data, t_listnode *next)
{
	t_listnode *newnode;

	newnode = (t_listnode *)malloc(sizeof(t_listnode));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->next = next;
	return (newnode);
}

size_t list_size(const t_list *list)
{
	if (!list)
		return (0);
	return (list->size);
}

bool list_is_empty(const t_list *list)
{
	if (!list || list->size == 0)
		return (TRUE);
	return (FALSE);
}

int list_value_at(const t_list *list, const size_t index)
{
	t_listnode *node;

	if (!list || (list->size - 1) < index || !list->head)
		return (-1);
	node = list->head;
	for (size_t i = 0; i < index; i++)
		node = node->next;
	return (node->data);
}

void list_push_front(t_list *list, int data)
{
	t_listnode *newnode;

	if (!list)
		return ;
	newnode = listnode_new(data, list->head);
	if (!newnode)
		return ;
	list->head = newnode;
	list->size++;
	if (list->size == 1)
		list->tail = newnode;
}

int list_pop_front(t_list *list)
{
	t_listnode *front;

	if (!list || !list->head)
		return (-1);
	front = list->head;
	list->head = front->next;
	if (!list->head)
		list->tail = NULL;
	list->size--;
	return (front->data);
}

void list_push_back(t_list *list, int data)
{
	t_listnode *newnode;

	if (!list)
		return ;
	newnode = listnode_new(data, NULL);
	if (!newnode)
		return ;
	if (list->tail)
		list->tail->next = newnode;
	list->tail = newnode;
	list->size++;
	if (list->size == 1)
		list->head = newnode;
}

int list_pop_back(t_list *list)
{
	t_listnode *back;
	t_listnode *node;

	if (!list || !list->tail)
		return (-1);
	back = list->tail;
	node = list->head;
	for (size_t i = 2; i < list->size; i++)
		node = node->next;
	node->next = NULL;
	list->size--;
	if (list->size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
		list->tail = node;
	return (back->data);
}

int list_front(t_list *list)
{
	if (!list || !list->head)
		return (-1);
	return (list->head->data);
}

int list_back(t_list *list)
{
	if (!list || !list->tail)
		return (-1);
	return (list->tail->data);
}

void list_insert(t_list *list, size_t index, int data)
{
	t_listnode *insert_prev;
	t_listnode *insert_next;
	t_listnode *newnode;

	if (!list || index > list->size)
		return ;
	insert_prev = list->head;
	insert_next = list->head;
	for (size_t i = 1; i < index; i++)
		insert_prev = insert_prev->next;
	if (index > 0)
		insert_next = insert_prev->next;
	newnode = listnode_new(data, insert_next);
	if (!newnode)
		return ;
	if (index > 0)
		insert_prev->next = newnode;
	else
		list->head = newnode;
	if (index == list->size)
		list->tail = newnode;
	list->size++;
}

void list_erase(t_list *list, size_t index)
{
	t_listnode *node;

	if (!list || index > list->size)
		return ;
	node = list->head;
	for (size_t i = 1; i < index; i++)
		node = node->next;
	if (index == 0)
		list->head = node->next;
	else if ((index - 1) == list->size)
	{
		list->tail = node;
		node->next = NULL;
	}
	else
		node->next = node->next->next;
	list->size--;
	if (list->size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
}

int list_value_n_from_end(t_list *list, size_t n)
{
	t_listnode *node;

	if (!list || n > list->size)
		return (-1);
	node = list->head;
	for (size_t i = 0; i < (list->size - n); i++)
		node = node->next;
	return (node->data);
}



