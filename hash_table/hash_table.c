#include "hash_table.h"

static int hash_table_hash(const char *key)
{
	int b;
	size_t dec;

	b = 31;
	dec = 0;
	// Rolling hash function
	for (int i = 0; key[i] != '\0'; i++)
		dec = dec + (b * key[i]);
	return (dec % TABLE_SIZE);
}

static int hash_table_search(const t_hash *h, const char *key)
{
	int keyhash;
	int count;

	if (!h || !key)
		return (-1);
	keyhash = hash_table_hash(key);
	count = 0;
	while (h->size > count && h->table[keyhash].key != key)
	{
		if (keyhash == h->size - 1)
			keyhash = 0;
		else
			keyhash += 1;
		count++;
	}
	if (h->table[keyhash].key == key)
		return (keyhash);
	return (-1);
}

t_hash *hash_table_create(const int size)
{
	t_hash *h;

	if (size <= 0)
		return (NULL);
	h = (t_hash *)malloc(sizeof(t_hash));
	if (!h)
		return (NULL);
	h->table = (t_slot *)malloc(sizeof(t_slot) * size);
	if (!h->table)
		return (NULL);
	h->size = size;
	for (int i = 0; i < h->size; i++)
	{
		h->table[i].flag = EMPTY;
		h->table[i].key = NULL;
		h->table[i].value = -1;
	}
	return (h);
}

void hash_table_add(t_hash *h, char *key, const int value)
{
	int keyhash;
	int count;

	if (!h || !key)
		return ;
	keyhash = hash_table_hash(key);
	count = 0;
	while (h->size > count && h->table[keyhash].flag == OCCUPIED)
	{
		if (keyhash + 1 >= h->size)
			keyhash = 0;
		else
			keyhash += 1;
		count++;
	}
	if (h->size == count)
	{
		printf("Error: table is full\n");
		return ;
	}
	h->table[keyhash].flag = OCCUPIED;
	h->table[keyhash].key = key;
	h->table[keyhash].value = value;
}

int hash_table_get(const t_hash *h, const char *key)
{
	int keyhash;

	keyhash = hash_table_search(h, key);
	if (keyhash == -1)
	{
		printf("Error: key does not exist in the table\n");
		return (-1);
	}
	return (h->table[keyhash].value);
}

t_bool hash_table_exists(const t_hash *h, const char *key)
{
	int keyhash;

	keyhash = hash_table_search(h, key);
	if (keyhash == -1)
	{
		printf("Error: key does not exist in the table\n");
		return (FALSE);
	}
	return (TRUE);
}

void hash_table_remove(t_hash *h, const char *key)
{
	int keyhash;

	keyhash = hash_table_search(h, key);
	if (keyhash == -1)
		return ;
	h->table[keyhash].flag = DELETED;
	h->table[keyhash].key = NULL;
	h->table[keyhash].value = -1;
}

void hash_table_destroy(t_hash *h)
{
	if (h)
	{
		if (h->table)
			free(h->table);
		free(h);
	}
}

void hash_table_debug(const t_hash *h)
{
	char *flag_strings[] = {"EMPTY", "OCCUPIED", "DELETED"};

	if (!h)
		return ;
	for (int i = 0; i < h->size; i++)
		printf("%d| %s | key: %s | val: %d\n", i, flag_strings[h->table[i].flag], h->table[i].key, h->table[i].value);
}