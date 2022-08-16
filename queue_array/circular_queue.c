#include "circular_queue.h"

t_cqueue *cqueue_new(void)
{
	t_cqueue *q;

	q = (t_cqueue *)malloc(sizeof(t_cqueue));
	if (!q)
		return (NULL);
	memset(q->queue, 0, sizeof(int) * max_length);
	q->length = max_length;
	q->write = 0;
	q->read = 0;
	return (q);
}

void cqueue_destroy(t_cqueue *q)
{
	if (q)
		free(q);
}

void cqueue_enqueue(t_cqueue *q, const int key)
{
	if (!q)
		return ;
	if (cqueue_full(q))
	{
		printf("queue: Circular queue is full\n");
		return ;
	}
	else if (q->write == (q->length - 1))
	{
		q->queue[q->write] = key;
		q->write = 0;
	}
	else
	{
		q->queue[q->write] = key;
		q->write++;
	}
}

int cqueue_dequeue(t_cqueue *q)
{
	int dequeue_key;

	if (!q || cqueue_empty(q))
		return (-1);
	dequeue_key = q->queue[q->read];
	q->queue[q->read] = 0;
	if (q->read == (q->length - 1))
		q->read = 0;
	else
		q->read++;
	return (dequeue_key);
}

t_bool cqueue_empty(t_cqueue *q)
{
	if (!q || q->write == q->read)
		return (TRUE);
	return (FALSE);
}

t_bool cqueue_full(t_cqueue *q)
{
	if (!q)
		return (FALSE);
	if (q->read == (q->write + 1) % q->length)
		return (TRUE);
	return (FALSE);
}

void cqueue_debug(t_cqueue *q)
{
	if (!q)
		return ;
	for (int i = 0; i < q->length; i++)
		printf("%d ", q->queue[i]);
	printf("\n");
}