#include "vector.h"

t_vector *vector_new(void)
{
	t_vector *new;

	new = (t_vector *)malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->array = NULL;
	new->size = 0;
	new->capacity = sizeof(t_vector);
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
	int *newarray;

	if (!v)
		return ;
	newarray = (int *)malloc(sizeof(int) * (v->size + 1));
	if (!newarray)
		return ;
	v->capacity += sizeof(int);
	for (size_t i = 0; i < v->size; i++)
		newarray[i] = v->array[i];
	newarray[v->size] = item;
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->size++;
}

void vector_insert(t_vector *v, const size_t index, const int item)
{
	int *newarray;

	if (!v || index > v->size)
		return ;
	newarray = (int *)malloc(sizeof(int) * (v->size + 1));
	if (!newarray)
		return ;
	v->capacity += sizeof(int);
	for (size_t i = 0; i < index; i++)
		newarray[i] = v->array[i];
	newarray[index] = item;
	for (size_t i = index; i < v->size; i++)
		newarray[i + 1] = v->array[i];
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->size++;
}

void vector_prepend(t_vector *v, const int item)
{
	int *newarray;

	if (!v)
		return ;
	newarray = (int *)malloc(sizeof(int) * (v->size + 1));
	if (!newarray)
		return ;
	v->capacity += sizeof(int);
	newarray[0] = item;
	for (size_t i = 0; i < v->size; i++)
		newarray[i + 1] = v->array[i];
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->size++;
}

int vector_pop(t_vector *v)
{
	int pop_val;
	int *newarray;

	if (!v || v->size == 0)
		return (0);
	newarray = (int *)malloc(sizeof(int) * (v->size - 1));
	if (!newarray)
		return (0);
	v->capacity -= sizeof(int);
	for (size_t i = 0; i < (v->size - 1); i++)
		newarray[i] = v->array[i];
	pop_val = v->array[v->size - 1];
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->size--;
	return (pop_val);
}

void vector_delete(t_vector *v, const size_t index)
{
	int *newarray;

	if (!v || v->size == 0 || index >= v->size)
		return ;
	newarray = (int *)malloc(sizeof(int) * (v->size - 1));
	if (!newarray)
		return ;
	v->capacity -= sizeof(int);
	for (size_t i = 0; i < index; i++)
		newarray[i] = v->array[i];
	for (size_t i = index + 1; i < v->size; i++)
		newarray[i - 1] = v->array[i];
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->size--;
}

void vector_remove(t_vector *v, const int item)
{
	int *newarray;
	size_t item_count;
	size_t slow;

	if (!v)
		return ;
	newarray = (int *)malloc(sizeof(int) * v->size);
	if (!newarray)
		return ;
	slow = 0;
	item_count = 0;
	for (size_t i = 0; i < v->size; i++)
	{
		if (v->array[i] == item)
			item_count++;
		else
		{
			newarray[slow] = v->array[i];
			slow++;
		}
	}
	if (v->array)
		free(v->array);
	v->array = newarray;
	v->capacity -= (sizeof(int) * item_count);
	v->size -= item_count;
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

void vector_resize(t_vector *v)
{
	int *newarray;
	size_t newcapacity;
	size_t capacity_as_item;

	if (!v)
		return ;
	capacity_as_item = (v->capacity - 24) / sizeof(int);
	if (v->size == 0)
	{
		newarray = (int *)malloc(sizeof(int));
		newcapacity = sizeof(int);
	}
	else if (v->size == capacity_as_item && v->size <= (SIZE_MAX / (sizeof(int) * 2)))
	{
		newarray = (int *)malloc(sizeof(int) * (v->size * 2));
		newcapacity = v->size * (sizeof(int) * 2);
	}
	else if (v->size <= capacity_as_item / 4)
	{
		newarray = (int *)malloc(sizeof(int) * (v->size / 2));
		newcapacity = (v->size / 2) * sizeof(int);
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
	v->capacity = sizeof(t_vector) + newcapacity;
}
