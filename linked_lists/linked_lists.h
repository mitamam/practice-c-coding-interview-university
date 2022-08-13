#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stdlib.h>
#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct	s_listnode
{
	int data;
	struct s_listnode *next;
}				t_listnode;

typedef struct	s_list
{
	size_t size;
	struct s_listnode *head;
	struct s_listnode *tail;
}				t_list;

t_list *list_new(void);
void list_destroy(t_list *list);
t_listnode *listnode_new(const int data, t_listnode *next);
size_t list_size(const t_list *list);
t_bool list_is_empty(const t_list *list);
int list_value_at(const t_list *list, const size_t index);
void list_push_front(t_list *list, int data);
int list_pop_front(t_list *list);
void list_push_back(t_list *list, int data);
int list_pop_back(t_list *list);
int list_front(const t_list *list);
int list_back(const t_list *list);
void list_insert(t_list *list, const size_t index, const int data);
void list_erase(t_list *list, const size_t index);
int list_value_n_from_end(t_list *list, const size_t n);
void list_reverse(t_list *list);
void list_remove_value(t_list *list, const int data);

#endif