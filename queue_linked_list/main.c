#include "queue.h"

int main(void)
{
	t_queue *q;

	q = queue_new();

	queue_enqueue(q, 1);
	queue_enqueue(q, 2);
	queue_enqueue(q, 3);
	queue_enqueue(q, 4);
	queue_enqueue(q, 5);

	printf("%d\n", queue_dequeue(q));
	printf("%d\n", queue_dequeue(q));
	queue_debug(q);
	printf("tail: %d\n", q->tail->key);
	printf("%d\n", queue_is_empty(q));

	queue_dequeue(q);
	queue_dequeue(q);
	queue_dequeue(q);
	printf("%d\n", queue_is_empty(q));
	printf("%p\n", q->tail);


	queue_destroy(q);

	return 0;
}