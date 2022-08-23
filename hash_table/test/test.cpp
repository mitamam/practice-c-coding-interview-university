#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
	#include "../hash_table.h"
}

TEST(HashTableTest, HashTableCreate)
{
	t_hash *h, *h2, *h3;

	h = hash_table_create(0);
	EXPECT_EQ(NULL, h);
	if (h)
		hash_table_destroy(h);

	h2 = hash_table_create(INT_MIN); // negative size
	EXPECT_EQ(NULL, h2);
	if (h2)
		hash_table_destroy(h2);

	h3 = hash_table_create(997);
	EXPECT_EQ(997, h3->size);
	for (int i = 0; i < 997; i++)
	{
		EXPECT_EQ(EMPTY, h3->table[i].flag);
		EXPECT_STREQ(NULL, h3->table[i].key);
		EXPECT_EQ(-1, h3->table[i].value);
	}
	if (h3)
		hash_table_destroy(h3);
}

TEST(HashTableTest, HashTableAdd)
{
	t_hash *h, *h2, *h3;
	char s1[] = "abcd";
	char s2[] = "efgh";
	char s3[1000001];

	h = hash_table_create(2);
	hash_table_add(NULL, s1, 10);
	hash_table_add(NULL, s2, 20);
	EXPECT_EQ(EMPTY, h->table[0].flag);
	EXPECT_STREQ(NULL, h->table[0].key);
	EXPECT_EQ(-1, h->table[0].value);
	EXPECT_EQ(EMPTY, h->table[1].flag);
	EXPECT_STREQ(NULL, h->table[1].key);
	EXPECT_EQ(-1, h->table[1].value);
	if (h)
		hash_table_destroy(h);

	h2 = hash_table_create(1);
	hash_table_add(h, NULL, 10);
	EXPECT_EQ(EMPTY, h->table[0].flag);
	EXPECT_STREQ(NULL, h->table[0].key);
	EXPECT_EQ(-1, h->table[0].value);
	if (h2)
		hash_table_destroy(h2);

	h3 = hash_table_create(1);
	for (int i = 0; i < 1000000; i++)
		s3[i] = '.';
	s3[1000000] = '\0';
	hash_table_add(h, s3, 100); // long key
	EXPECT_EQ(OCCUPIED, h->table[0].flag);
	EXPECT_STREQ(s3, h->table[0].key);
	EXPECT_EQ(100, h->table[0].value);
	hash_table_add(h, s1, 10); // table is full
	EXPECT_EQ(OCCUPIED, h->table[0].flag);
	EXPECT_STREQ(s3, h->table[0].key);
	EXPECT_EQ(100, h->table[0].value);
	if (h3)
		hash_table_destroy(h3);
}

TEST(HashTableTest, HashTableGet)
{
	t_hash *h;
	char s1[] = "abcd";
	char s2[1000001];

	h = hash_table_create(1);
	EXPECT_EQ(-1, hash_table_get(NULL, s1));
	EXPECT_EQ(-1, hash_table_get(h, NULL));
	EXPECT_EQ(-1, hash_table_get(h, s1));

	for (int i = 0; i < 1000000; i++)
		s2[i] = '.';
	s2[1000000] = '\0';
	hash_table_add(h, s2, 100); // long key
	EXPECT_EQ(100, hash_table_get(h, s2));
	EXPECT_EQ(-1, hash_table_get(h, s1));

	if (h)
		hash_table_destroy(h);
}

TEST(HashTableTest, HashTableExists)
{
	t_hash *h;
	char s1[] = "abcd";
	char s2[1000001];

	h = hash_table_create(1);
	EXPECT_EQ(FALSE, hash_table_exists(NULL, s1));
	EXPECT_EQ(FALSE, hash_table_exists(h, NULL));
	EXPECT_EQ(FALSE, hash_table_exists(h, s1));

	for (int i = 0; i < 1000000; i++)
		s2[i] = '.';
	s2[1000000] = '\0';
	hash_table_add(h, s2, 100); // long key
	EXPECT_EQ(TRUE, hash_table_exists(h, s2));
	EXPECT_EQ(FALSE, hash_table_exists(h, s1));

	if (h)
		hash_table_destroy(h);
}

TEST(HashTableTest, HashTableRemove)
{
	t_hash *h;
	char s1[] = "abcd";
	char s2[1000001];

	h = hash_table_create(1);
	hash_table_remove(NULL, s1);
	hash_table_remove(h, s1);

	for (int i = 0; i < 1000000; i++)
		s2[i] = '.';
	s2[1000000] = '\0';
	hash_table_add(h, s2, 100); // long key
	hash_table_remove(h, NULL);
	EXPECT_EQ(OCCUPIED, h->table[0].flag);
	EXPECT_STREQ(s2, h->table[0].key);
	EXPECT_EQ(100, h->table[0].value);

	hash_table_remove(h, s1);
	EXPECT_EQ(OCCUPIED, h->table[0].flag);
	EXPECT_STREQ(s2, h->table[0].key);
	EXPECT_EQ(100, h->table[0].value);

	hash_table_remove(h, s2);
	EXPECT_EQ(DELETED, h->table[0].flag);
	EXPECT_STREQ(NULL, h->table[0].key);
	EXPECT_EQ(-1, h->table[0].value);
	hash_table_add(h, s1, 10);
	EXPECT_EQ(OCCUPIED, h->table[0].flag);
	EXPECT_STREQ(s1, h->table[0].key);
	EXPECT_EQ(10, h->table[0].value);

	if (h)
		hash_table_destroy(h);
}