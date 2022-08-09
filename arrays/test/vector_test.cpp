#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../vector.h"
}

TEST(VectorTest, VectorNew)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(NULL, v->array);
	EXPECT_EQ(0, v->capacity);
	EXPECT_EQ(0, v->size);

	vector_destroy(v);
}

TEST(VectorTest, VectorPush)
{
	t_vector *v, *v2;

	v = vector_new();
	v2 = vector_new();

	vector_push(v, INT_MAX); // Input 2147483647 (INT_MAX)
	EXPECT_EQ(INT_MAX, v->array[0]);
	vector_push(v, INT_MIN); // Input -2147483648 (INT_MIN)
	EXPECT_EQ(INT_MIN, v->array[1]);

	vector_push(v2, 1);
	vector_push(v2, 2);
	vector_push(v2, 3);
	vector_push(v2, 4);
	for (int i = 0; i < v2->size; i++)
		ASSERT_EQ(i + 1, v2->array[i]);

	vector_destroy(v);
	vector_destroy(v2);
}

TEST(VectorTest, VectorInsert)
{
	t_vector *v;

	v = vector_new();

	vector_insert(v, 0, INT_MAX); // Input 2147483647 (INT_MAX)
	vector_insert(v, 0, INT_MIN); // Input -2147483648 (INT_MIN)
	EXPECT_EQ(INT_MAX, v->array[1]);
	EXPECT_EQ(INT_MIN, v->array[0]);

	vector_insert(v, 1, 0); // Input 0
	EXPECT_EQ(0, v->array[1]);

	vector_insert(v, 3, 100); // Last index
	EXPECT_EQ(100, v->array[3]);

	vector_insert(v, 10, 200); // Invalid index

	vector_destroy(v);
}

TEST(VectorTest, VectorPrepend)
{
	t_vector *v;

	v = vector_new();

	vector_prepend(v, 3);
	vector_prepend(v, 2);
	vector_prepend(v, 1);
	for (size_t i = 0; i < v->size; i++)
		EXPECT_EQ(i + 1, v->array[i]);

	vector_prepend(v, INT_MAX); // Input 2147483647 (INT_MAX)
	EXPECT_EQ(INT_MAX, v->array[0]);
	vector_prepend(v, INT_MIN); // Input -2147483648 (INT_MIN)
	EXPECT_EQ(INT_MIN, v->array[0]);

	vector_destroy(v);
}

TEST(VectorTest, VectorPop)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(0, vector_pop(NULL)); // NULL

	EXPECT_EQ(0, vector_pop(v)); // Empty array

	for (size_t i = 0; i < 3; i++)
		vector_push(v, i + 1);
	EXPECT_EQ(3, vector_pop(v));
	EXPECT_EQ(2, vector_pop(v));
	EXPECT_EQ(1, vector_pop(v));

	vector_destroy(v);
}

TEST(VectorTest, VectorDelete)
{
	t_vector *v;

	v = vector_new();

	vector_delete(v, 0); // Empty array

	for (size_t i = 0; i < 5; i++)
		vector_push(v, i + 1);
	vector_delete(v, 0); // First index
	EXPECT_EQ(2, v->array[0]);
	EXPECT_EQ(5, v->array[3]);

	vector_delete(v, 3); // Last index
	for (size_t i = 0; i < v->size; i++)
		EXPECT_EQ(i + 2, v->array[i]);
	
	vector_delete(v, 10); // Invalid index

	vector_destroy(v);
}

TEST(VectorTest, VectorRemove)
{
	t_vector *v;

	v = vector_new();

	for (int i = 0; i < 5; i++)
		vector_push(v, 1);
	vector_remove(v, 1); // Same value
	EXPECT_EQ(0, v->size);

	vector_remove(v, 1); // Empty array

	for (int i = 0; i < 5; i++)
		vector_push(v, i + 1);
	vector_remove(v, 1); // First value
	EXPECT_EQ(2, v->array[0]);

	vector_remove(v, 5); // Last value
	EXPECT_EQ(4, v->array[v->size - 1]);

	vector_remove(v, 100); // Not found

	vector_prepend(v, INT_MAX); 
	vector_prepend(v, INT_MIN);
	vector_remove(v, INT_MAX); // Remove 2147483647 (INT_MAX)
	EXPECT_EQ(INT_MIN, v->array[0]);
	vector_remove(v, INT_MIN); // Remove -2147483648 (INT_MIN)
	EXPECT_EQ(2, v->array[0]);

	vector_destroy(v);
}

TEST(VectorTest, VectorSize)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(0, vector_size(v)); // Initialized value

	for (int i = 0; i < 3; i++)
		vector_push(v, i + 1);
	EXPECT_EQ(3, vector_size(v)); // push()

	vector_pop(v);
	vector_pop(v);
	EXPECT_EQ(1, vector_size(v)); // pop()

	vector_pop(v);
	EXPECT_EQ(0, vector_size(v)); // Empty array

	for (int i = 0; i < 10; i++)
		vector_insert(v, i, i + 1);
	EXPECT_EQ(10, vector_size(v)); // insert()

	for (int i = 0; i < 5; i++)
		vector_delete(v, 0);
	EXPECT_EQ(5, vector_size(v)); // delete()

	vector_remove(v, 10);
	vector_remove(v, 9);
	EXPECT_EQ(3, vector_size(v)); // remove()

	vector_prepend(v, 5);
	EXPECT_EQ(4, vector_size(v)); // prepend()

	vector_destroy(v);
}

TEST(VectorTest, VectorCapacity)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(0, vector_capacity(v)); // Initialized value

	vector_push(v, 1);
	EXPECT_EQ(4, vector_capacity(v));

	for (int i = 1; i < 100; i++)
		vector_push(v, i + 1);
	EXPECT_EQ(128, vector_capacity(v) / 4);

	for (int i = 100; i < 200; i++)
		vector_push(v, i + 1);
	// is capacity greater than v->size * sizeof(int)?
	EXPECT_LE(vector_size(v), vector_capacity(v) / 4);

	vector_destroy(v);
}

TEST(VectorTest, VectorIsEmpty)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(TRUE, vector_is_empty(v)); // Empty array

	vector_push(v, 1);
	EXPECT_EQ(FALSE, vector_is_empty(v)); // Not empty array

	vector_destroy(v);
}

TEST(VectorTest, VectorAt)
{
	t_vector *v;

	v = vector_new();

	EXPECT_EQ(-1, vector_at(NULL, 0)); // NULL

	EXPECT_EQ(-1, vector_at(v, 1)); // Invalid index

	for (int i = 0; i < 5; i++)
		vector_push(v, i + 1);
	EXPECT_EQ(1, vector_at(v, 0)); // First index
	EXPECT_EQ(3, vector_at(v, 2)); // Middle index
	EXPECT_EQ(5, vector_at(v, 4)); // Last index

	vector_destroy(v);
}

TEST(VectorTest, VectorFind)
{
	t_vector *v;
	t_vector *v2;

	v = vector_new();
	v2 = vector_new();

	EXPECT_EQ(-1, vector_find(NULL, 1)); // NULL

	vector_push(v, 1);
	vector_push(v, 1);
	vector_push(v, 1);
	EXPECT_EQ(0, vector_find(v, 1)); // Same values

	vector_prepend(v, INT_MAX); 
	vector_prepend(v, INT_MIN);
	EXPECT_EQ(1, vector_find(v, INT_MAX)); // Find 2147483647 (INT_MAX)
	EXPECT_EQ(0, vector_find(v, INT_MIN)); // Find -2147483648 (INT_MAX)

	EXPECT_EQ(-1, vector_find(v, 100)); // not found

	for (int i = 0; i < 10; i++)
		vector_push(v2, i + 1);
	EXPECT_EQ(9, vector_find(v2, 10)); // at the end
	EXPECT_EQ(0, vector_find(v2, 1)); // at the first
	EXPECT_EQ(4, vector_find(v2, 5)); // at the middle

	vector_destroy(v);
	vector_destroy(v2);
}
