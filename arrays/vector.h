#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum t_bool
{
	FALSE,
	TRUE
}			e_bool;

typedef struct	s_vector
{
	int *array;
	size_t size;
	size_t capacity;
}				t_vector;

t_vector *vector_new(void);
void vector_destroy(t_vector *v);

size_t vector_size(const t_vector *v);
size_t vector_capacity(const t_vector *v);
e_bool vector_is_empty(const t_vector *v);
int vector_at(const t_vector *v, const size_t index);
void vector_push(t_vector *v, const int item);
void vector_insert(t_vector *v, const size_t index, const int item);
void vector_prepend(t_vector *v, const int item);
int vector_pop(t_vector *v);
void vector_delete(t_vector *v, const size_t index);
void vector_remove(t_vector *v, const int item);
int vector_find(t_vector *v, const int item);

#endif /* VECTOR_H */