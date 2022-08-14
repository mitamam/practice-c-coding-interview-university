#include "queue.h"

static t_qnode *queue_newnode(const int key, t_qnode *next)
{
	t_qnode *node;

	node = (t_qnode *)malloc(sizeof(t_qnode));
	if (!node)
		return (NULL);
	node->key = key;
	node->next = next;
	return (node);
}

t_queue *queue_new(void)
{
	t_queue *q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->head = NULL;
	q->tail = NULL;
	return (q);
}

void queue_destroy(t_queue *q)
{
	t_qnode *node, *next;

	if (q)
	{
		if (q->head)
		{
			node = q->head;
			while (node)
			{
				next = node->next;
				free(node);
				node = next;
			}
		}
		free(q);
	}
}

void queue_enqueue(t_queue *q, const int key)
{
	t_qnode *node;

	if (!q)
		return ;
	node = queue_newnode(key, NULL);
	if (!node)
		return ;
	if (q->tail)
		q->tail->next = node;
	else
		q->head = node;
	q->tail = node;
}

int queue_dequeue(t_queue *q)
{
	int front;

	if (!q || !q->head)
		return (-1);
	front = q->head->key;
	q->head = q->head->next;
	if (!q->head)
		q->tail = NULL;
	return (front);
}

t_bool queue_is_empty(const t_queue *q)
{
	if (!q || !q->head)
		return (TRUE);
	return (FALSE);
}

void queue_debug(const t_queue *q)
{
	if (!q || !q->head)
		printf("ERROR: queue is empty");
	for (t_qnode *node = q->head; node != NULL; node = node->next)
		printf("%d ", node->key);
	printf("\n");
}
