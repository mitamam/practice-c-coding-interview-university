#include "vector.h"

static void vector_resize(t_vector *v)
{
	int *newarray;
	size_t newcapacity;
	size_t capacity_as_item;

	if (!v)
		return ;
	capacity_as_item = v->capacity / sizeof(int);
	if (v->size == 0)
	{
		newarray = (int *)malloc(sizeof(int));
		newcapacity = sizeof(int);
	}
	else if (v->size == capacity_as_item && v->capacity <= SIZE_MAX / 2)
	{
		newarray = (int *)malloc(v->capacity * 2);
		newcapacity = v->capacity * 2;
	}
	else if (v->size <= capacity_as_item / 4)
	{
		newarray = (int *)malloc(v->capacity / 2);
		newcapacity = v->capacity / 2;
	}
	else
		return ;
	if (!newarray)
		return ;
	for (size_t i = 0; i < v->size; i++)
		newarray[i] = v->array[i];
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->capacity = newcapacity;
}

t_vector *vector_new(void)
{
	t_vector *new;

	new = (t_vector *)malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->array = NULL;
	new->size = 0;
	new->capacity = 0;
	return (new);
}

void vector_destroy(t_vector *v)
{
	if (v)
	{
		if (v->array)
			free(v->array);
		free(v);
	}
}

size_t vector_size(const t_vector *v)
{
	if (!v)
		return (0);
	return (v->size);
}

size_t vector_capacity(const t_vector *v)
{
	if (!v)
		return (0);
	return (v->capacity);
}

bool vector_is_empty(const t_vector *v)
{
	if (!v || v->size == 0)
		return (true);
	return (false);
}

int vector_at(const t_vector *v, const size_t index)
{
	if (!v || index >= v->size)
		return (-1);
	return (v->array[index]);
}

void vector_push(t_vector *v, const int item)
{
	if (!v)
		return ;
	vector_resize(v);
	v->array[v->size] = item; 
	v->size++;
}

void vector_insert(t_vector *v, const size_t index, const int item)
{
	if (!v || index > v->size)
		return ;
	vector_resize(v);
	for (size_t i = (v->size - 1); i >= index; i--)
		v->array[i + 1] = v->array[i];
	v->array[index] = item;
	v->size++;
}

void vector_prepend(t_vector *v, const int item)
{
	if (!v)
		return ;
	vector_resize(v);
	for (size_t i = v->size; i >= 1; i--)
		v->array[i] = v->array[i - 1];
	v->array[0] = item;
	v->size++;
}

int vector_pop(t_vector *v)
{
	int pop_val;

	if (!v || v->size == 0)
		return (0);
	pop_val = v->array[v->size - 1];
	v->array[v->size - 1] = 0;
	v->size--;
	vector_resize(v);
	return (pop_val);
}

void vector_delete(t_vector *v, const size_t index)
{
	if (!v || v->size == 0 || index >= v->size)
		return ;
	for (size_t i = index + 1; i < v->size; i++)
		v->array[i - 1] = v->array[i];
	v->size--;
	vector_resize(v);
}

void vector_remove(t_vector *v, const int item)
{
	size_t item_count;
	size_t slow;

	if (!v)
		return ;
	slow = 0;
	item_count = 0;
	for (size_t i = 0; i < v->size; i++)
	{
		if (v->array[i] == item)
			item_count++;
		else
		{
			v->array[slow] = v->array[i];
			slow++;
		}
	}
	for (size_t i = (v->size - item_count); i < v->size; i++)
		v->array[i] = 0;
	v->size -= item_count;
	vector_resize(v);
}

int vector_find(t_vector *v, const int item)
{
	if (!v)
		return (-1);
	for (size_t i = 0; i < v->size; i++)
	{
		if (v->array[i] == item)
			return (i);
	}
	return (-1);
}
