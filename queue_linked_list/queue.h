#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_qnode
{
	int key;
	struct s_qnode *next;
}				t_qnode;

typedef struct s_queue
{
	struct s_qnode *head;
	struct s_qnode *tail;
}				t_queue;

t_queue *queue_new(void);
void queue_destroy(t_queue *q);
void queue_enqueue(t_queue *q, const int key);
int queue_dequeue(t_queue *q);
t_bool queue_is_empty(const t_queue *q);

void queue_debug(const t_queue *q);

#endif /* QUEUE_H */