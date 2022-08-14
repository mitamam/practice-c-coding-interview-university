#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../queue.h"
}

TEST(QueueLinkedListTest, QueueNew)
{
	t_queue *q;

	q = queue_new();

	EXPECT_EQ(NULL, q->head);
	EXPECT_EQ(NULL, q->tail);

	if (q)
		queue_destroy(q);
}

TEST(QueueLinkedListTest, QueueEnqueue)
{
	t_queue *q;
	t_queue *q2;

	q = queue_new();
	q2 = queue_new();

	queue_enqueue(NULL, 100);

	queue_enqueue(q, INT_MIN);
	EXPECT_EQ(INT_MIN, q->head->key);
	EXPECT_EQ(INT_MIN, q->tail->key);
	queue_enqueue(q, INT_MAX);
	EXPECT_EQ(INT_MAX, q->head->next->key);
	EXPECT_EQ(INT_MAX, q->tail->key);

	queue_enqueue(q2, 1);
	queue_enqueue(q2, 2);
	queue_enqueue(q2, 3);
	queue_enqueue(q2, 4);
	queue_enqueue(q2, 5);
	EXPECT_EQ(1, q2->head->key);
	EXPECT_EQ(2, q2->head->next->key);
	EXPECT_EQ(3, q2->head->next->next->key);
	EXPECT_EQ(4, q2->head->next->next->next->key);
	EXPECT_EQ(5, q2->tail->key);

	if (q)
		queue_destroy(q);
	if (q2)
		queue_destroy(q2);
}

TEST(QueueLinkedListTest, QueueDequeue)
{
	t_queue *q;

	q = queue_new();
	if (!q)
		return ;

	EXPECT_EQ(-1, queue_dequeue(NULL));
	EXPECT_EQ(-1, queue_dequeue(q));

	queue_enqueue(q, 1);
	EXPECT_EQ(1, queue_dequeue(q));
	EXPECT_EQ(NULL, q->head);
	EXPECT_EQ(NULL, q->tail);

	for (int i = 1; i <= 5; i++)
		queue_enqueue(q, i);
	EXPECT_EQ(1, queue_dequeue(q));
	EXPECT_EQ(2, queue_dequeue(q));
	EXPECT_EQ(3, q->head->key);
	EXPECT_EQ(4, q->head->next->key);
	EXPECT_EQ(5, q->head->next->next->key);

	queue_destroy(q);
}

TEST(QueueLinkedListTest, QueueIsEmpty)
{
	t_queue *q;

	q = queue_new();
	if (!q)
		return ;

	EXPECT_EQ(TRUE, queue_is_empty(NULL));
	EXPECT_EQ(TRUE, queue_is_empty(q));

	queue_enqueue(q, 1);
	EXPECT_EQ(FALSE, queue_is_empty(q));

	queue_destroy(q);
}