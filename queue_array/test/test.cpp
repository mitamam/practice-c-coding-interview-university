#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../circular_queue.h"
}

TEST(CircularQueueTest, CircularQueueNew)
{
	t_cqueue *q;

	q = cqueue_new();
	if (!q)
		return ;

	EXPECT_EQ(max_length, q->length);
	EXPECT_EQ(0, q->write);
	EXPECT_EQ(0, q->read);

	cqueue_destroy(q);
}

TEST(CircularQueueTest, CircularQueueEnqueue)
{
	t_cqueue *q;
	t_cqueue *q2;

	q = cqueue_new();
	if (!q)
		return ;
	q2 = cqueue_new();
	if (!q2)
		return ;

	cqueue_enqueue(NULL, 100);

	cqueue_enqueue(q, INT_MIN);
	EXPECT_EQ(INT_MIN, q->queue[0]);
	cqueue_enqueue(q, INT_MAX);
	EXPECT_EQ(INT_MAX, q->queue[1]);

	cqueue_enqueue(q2, 1);
	cqueue_enqueue(q2, 2);
	cqueue_enqueue(q2, 3);
	cqueue_enqueue(q2, 4);
	cqueue_enqueue(q2, 5);
	cqueue_enqueue(q2, 6);
	EXPECT_EQ(1, q2->queue[0]);
	EXPECT_EQ(2, q2->queue[1]);
	EXPECT_EQ(3, q2->queue[2]);
	EXPECT_EQ(4, q2->queue[3]);
	EXPECT_EQ(5, q2->queue[4]);
	EXPECT_EQ(6, q2->queue[5]);
	cqueue_enqueue(q2, 7); // full

	cqueue_destroy(q);
	cqueue_destroy(q2);
}

TEST(CircularQueueTest, CircularQueueDequeue)
{
	t_cqueue *q;

	q = cqueue_new();
	if (!q)
		return ;

	EXPECT_EQ(-1, cqueue_dequeue(NULL));
	EXPECT_EQ(-1, cqueue_dequeue(q));

	cqueue_enqueue(q, 1);
	EXPECT_EQ(1, cqueue_dequeue(q));
	EXPECT_EQ(TRUE, cqueue_empty(q));

	for (int i = 1; i <= (max_length - 1) ; i++)
		cqueue_enqueue(q, i);
	EXPECT_EQ(1, cqueue_dequeue(q));
	EXPECT_EQ(2, cqueue_dequeue(q));
	cqueue_enqueue(q, 7);
	cqueue_enqueue(q, 8);
	EXPECT_EQ(3, cqueue_dequeue(q));
	EXPECT_EQ(4, cqueue_dequeue(q));
	EXPECT_EQ(5, cqueue_dequeue(q));
	EXPECT_EQ(6, cqueue_dequeue(q));
	EXPECT_EQ(7, cqueue_dequeue(q));
	EXPECT_EQ(8, cqueue_dequeue(q));

	cqueue_destroy(q);
}

TEST(CircularQueueTest, CircularQueueEmpty)
{
	t_cqueue *q;

	q = cqueue_new();
	if (!q)
		return ;
	
	EXPECT_EQ(TRUE, cqueue_empty(NULL));
	EXPECT_EQ(TRUE, cqueue_empty(q));

	cqueue_enqueue(q, 1);
	EXPECT_EQ(FALSE, cqueue_empty(q));
	cqueue_dequeue(q);
	EXPECT_EQ(TRUE, cqueue_empty(q));

	cqueue_destroy(q);
}

TEST(CircularQueueTest, CircularQueueFull)
{
	t_cqueue *q;

	q = cqueue_new();
	if (!q)
		return ;
	
	EXPECT_EQ(FALSE, cqueue_full(NULL));
	EXPECT_EQ(FALSE, cqueue_full(q));

	for (int i = 1; i < (max_length - 1); i++)
		cqueue_enqueue(q, i);
	EXPECT_EQ(FALSE, cqueue_full(q));
	cqueue_enqueue(q, 6);
	EXPECT_EQ(TRUE, cqueue_full(q));
	cqueue_dequeue(q);
	EXPECT_EQ(FALSE, cqueue_full(q));

	cqueue_destroy(q);
}