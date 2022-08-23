#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>

#define TABLE_SIZE 5


typedef enum e_flag
{
	EMPTY,
	OCCUPIED,
	DELETED
}			t_flag;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_slot
{
	enum e_flag flag;
	char *key;
	int value;
}				t_slot;

typedef struct s_hash 
{
	int size;
	struct s_slot *table;
}				t_hash;

t_hash *hash_table_create(const int size);
void hash_table_add(t_hash *h, char *key, const int value);
int hash_table_get(const t_hash *h, const char *key);
t_bool hash_table_exists(const t_hash *h, const char *key);
void hash_table_remove(t_hash *h, const char *key);
void hash_table_destroy(t_hash *h);

void hash_table_debug(const t_hash *h);

#endif /* HASH_TABLE_H */