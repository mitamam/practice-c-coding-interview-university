#ifndef CIRCULAR_QUEUE_H
# define CIRCULAR_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max_length 7

typedef enum e_bool {
	FALSE,
	TRUE
}			t_bool;

typedef struct s_cqueue
{
	int queue[max_length];
	int length;
	int write;
	int read;
}				t_cqueue;

t_cqueue *cqueue_new(void);
void cqueue_destroy(t_cqueue *q);
void cqueue_enqueue(t_cqueue *q, const int key);
int cqueue_dequeue(t_cqueue *q);
t_bool cqueue_empty(t_cqueue *q);
t_bool cqueue_full(t_cqueue *q);

void cqueue_debug(t_cqueue *q);

#endif /* CIRCULAR_QUEUE_H */