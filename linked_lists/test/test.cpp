#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../linked_lists.h"
}

TEST(LinkedListsTest, ListNew)
{
	t_list *list;

	list = list_new();
	
	EXPECT_EQ(0, list->size);
	EXPECT_EQ(NULL, list->head);
	EXPECT_EQ(NULL, list->tail);

	list_destroy(list);
}

TEST(LinkedListsTest, ListPushFront)
{
	t_list *list;
	t_list *list2;

	list = list_new();
	list2 = list_new();

	list_push_front(NULL, 100);
	
	list_push_front(list, INT_MAX);
	list_push_front(list, INT_MIN);
	EXPECT_EQ(INT_MIN, list->head->data);
	EXPECT_EQ(INT_MAX, list->head->next->data);

	list_push_front(list2, 1);
	EXPECT_EQ(1, list2->head->data);
	EXPECT_EQ(1, list2->tail->data);
	list_push_front(list2, 2);
	list_push_front(list2, 3);
	list_push_front(list2, 4);
	EXPECT_EQ(4, list2->head->data);
	EXPECT_EQ(3, list2->head->next->data);
	EXPECT_EQ(2, list2->head->next->next->data);
	EXPECT_EQ(1, list2->head->next->next->next->data);
	EXPECT_EQ(1, list2->tail->data);

	list_destroy(list);
	list_destroy(list2);
}

TEST(LinkedListsTest, ListPopFront)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_pop_front(NULL));
	EXPECT_EQ(-1, list_pop_front(list));

	for (int i = 1; i <= 10; i++)
		list_push_front(list, i);
	
	EXPECT_EQ(10, list_pop_front(list));
	EXPECT_EQ(9, list_pop_front(list));
	EXPECT_EQ(8, list_pop_front(list));
	EXPECT_EQ(7, list_pop_front(list));
	EXPECT_EQ(6, list_pop_front(list));
	EXPECT_EQ(5, list->head->data);
	EXPECT_EQ(1, list->tail->data);
	EXPECT_EQ(5, list->size);

	list_destroy(list);
}

TEST(LinkedListsTest, ListPushBack)
{
	t_list *list;
	t_list *list2;

	list = list_new();
	list2 = list_new();

	list_push_back(NULL, 100);
	
	list_push_back(list, INT_MAX);
	list_push_back(list, INT_MIN);
	EXPECT_EQ(INT_MAX, list->head->data);
	EXPECT_EQ(INT_MIN, list->head->next->data);

	list_push_back(list2, 1);
	EXPECT_EQ(1, list2->head->data);
	EXPECT_EQ(1, list2->tail->data);
	list_push_back(list2, 2);
	list_push_back(list2, 3);
	list_push_back(list2, 4);
	EXPECT_EQ(2, list2->head->next->data);
	EXPECT_EQ(3, list2->head->next->next->data);
	EXPECT_EQ(4, list2->head->next->next->next->data);
	EXPECT_EQ(4, list2->tail->data);

	list_destroy(list);
	list_destroy(list2);
}

TEST(LinkedListsTest, ListPopBack)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_pop_back(NULL));
	EXPECT_EQ(-1, list_pop_back(list));

	for (int i = 1; i <= 10; i++)
		list_push_back(list, i);
	
	EXPECT_EQ(10, list_pop_back(list));
	EXPECT_EQ(9, list_pop_back(list));
	EXPECT_EQ(8, list_pop_back(list));
	EXPECT_EQ(7, list_pop_back(list));
	EXPECT_EQ(6, list_pop_back(list));
	EXPECT_EQ(1, list->head->data);
	EXPECT_EQ(5, list->tail->data);
	EXPECT_EQ(5, list->size);

	list_destroy(list);
}

TEST(LinkedListsTest, ListSize)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(0, list_size(NULL));
	EXPECT_EQ(0, list_size(list));

	list_push_back(list, 1);
	EXPECT_EQ(1, list_size(list));
	list_push_back(list, 2);
	list_push_back(list, 3);
	EXPECT_EQ(3, list_size(list));

	list_pop_back(list);
	list_pop_back(list);
	list_pop_back(list);
	EXPECT_EQ(0, list_size(list));

	list_destroy(list);
}

TEST(LinkedListsTest, ListIsEmpty)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(TRUE, list_is_empty(NULL));
	EXPECT_EQ(TRUE, list_is_empty(list));

	list_push_back(list, 1);
	EXPECT_EQ(FALSE, list_is_empty(list));
	list_pop_back(list);
	EXPECT_EQ(TRUE, list_is_empty(list));

	list_destroy(list);
}

TEST(LinkedListsTest, ListValueAt)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_value_at(NULL, 0));
	EXPECT_EQ(-1, list_value_at(list, 0));

	for (int i = 1; i <= 10; i++)
		list_push_back(list, i);

	EXPECT_EQ(1, list_value_at(list, 0));
	EXPECT_EQ(5, list_value_at(list, 4));
	EXPECT_EQ(10, list_value_at(list, 9));

	EXPECT_EQ(-1, list_value_at(list, 100));

	list_destroy(list);
}

TEST(LinkedListsTest, ListFront)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_front(NULL));
	EXPECT_EQ(-1, list_front(list));

	list_push_back(list, 3);
	EXPECT_EQ(3, list_front(list));

	list_push_front(list, 2);
	list_push_front(list, 1);
	EXPECT_EQ(1, list_front(list));

	list_destroy(list);
}

TEST(LinkedListsTest, ListBack)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_back(NULL));
	EXPECT_EQ(-1, list_back(list));

	list_push_back(list, 3);
	EXPECT_EQ(3, list_back(list));

	list_push_back(list, 2);
	list_push_back(list, 1);
	EXPECT_EQ(1, list_back(list));

	list_destroy(list);
}

TEST(LinkedListsTest, ListInsert)
{
	t_list *list;

	list = list_new();

	list_insert(NULL, 0, 1);

	list_insert(list, 0, 1);
	EXPECT_EQ(1, list->head->data);

	for (int i = 2; i <= 5; i++)
		list_push_back(list, i);
	list_insert(list, 0, 0);
	EXPECT_EQ(0, list->head->data);

	list_insert(list, 2, 100);
	EXPECT_EQ(100, list->head->next->next->data);

	list_insert(list, (list->size - 1), 200);
	EXPECT_EQ(200, list->head->next->next->next->next->next->next->data);

	list_insert(list, list->size, 6);
	EXPECT_EQ(6, list->head->next->next->next->next->next->next->next->next->data);

	list_destroy(list);
}

TEST(LinkedListsTest, ListErase)
{
	t_list *list;

	list = list_new();

	list_erase(NULL, 0);
	list_erase(list, 0);

	for (int i = 1; i <= 5; i++)
		list_push_back(list, i);

	list_erase(list, 0);
	EXPECT_EQ(2, list->head->data);
	list_erase(list, 3);
	EXPECT_EQ(4, list->head->next->next->data);
	EXPECT_EQ(4, list->tail->data);

	list_erase(list, 100);

	list_destroy(list);
}

TEST(LinkedListsTest, ListValueNFromEnd)
{
	t_list *list;

	list = list_new();

	EXPECT_EQ(-1, list_value_n_from_end(NULL, 0));
	EXPECT_EQ(-1, list_value_n_from_end(list, 1));

	for (int i = 1; i <= 5; i++)
		list_push_back(list, i);
	EXPECT_EQ(-1, list_value_n_from_end(list, 0));
	EXPECT_EQ(5, list_value_n_from_end(list, 1));
	EXPECT_EQ(1, list_value_n_from_end(list, 5));

	EXPECT_EQ(-1, list_value_n_from_end(list, 10));

	list_destroy(list);
}

TEST(LinkedListsTest, ListReverse)
{
	t_list *list;

	list = list_new();

	list_reverse(NULL);
	list_reverse(list);

	list_push_back(list, 1);
	list_reverse(list);
	EXPECT_EQ(1, list->head->data);
	EXPECT_EQ(1, list->tail->data);
	list_pop_back(list);

	for (int i = 1; i <= 5; i++)
		list_push_back(list, i);

	list_reverse(list);
	EXPECT_EQ(5, list->head->data);
	EXPECT_EQ(4, list->head->next->data);
	EXPECT_EQ(3, list->head->next->next->data);
	EXPECT_EQ(2, list->head->next->next->next->data);
	EXPECT_EQ(1, list->head->next->next->next->next->data);
	EXPECT_EQ(1, list->tail->data);

	list_destroy(list);
}

TEST(LinkedListsTest, ListRemoveValue)
{
	t_list *list;
	t_list *list2;
	t_list *list3;

	list = list_new();
	list2 = list_new();
	list3 = list_new();

	list_remove_value(NULL, 0);
	list_remove_value(list, 0);

	list_push_back(list, INT_MAX);
	list_push_back(list, INT_MIN);
	list_remove_value(list, INT_MIN);
	EXPECT_EQ(INT_MAX, list->tail->data);
	EXPECT_EQ(NULL, list->head->next);

	list_remove_value(list, INT_MAX);
	EXPECT_EQ(NULL, list->head);
	EXPECT_EQ(NULL, list->tail);

	for (int i = 1; i <= 10; i++)
		list_push_back(list2, i);
	list_remove_value(list2, 1);
	EXPECT_EQ(2, list2->head->data);
	list_remove_value(list2, 5);
	EXPECT_EQ(6, list2->head->next->next->next->data);

	list_remove_value(list2, 100);

	list_push_back(list3, 1);
	list_push_back(list3, 1);
	list_push_back(list3, 1);
	list_remove_value(list3, 1);
	EXPECT_EQ(1, list3->head->data);
	EXPECT_EQ(1, list3->head->next->data);
	EXPECT_EQ(NULL, list3->head->next->next);

	list_destroy(list);
	list_destroy(list2);
	list_destroy(list3);
}