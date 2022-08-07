#include "vector.h"

int main(void)
{
	t_vector *v;

	v = vector_new();
	printf("size: %zu\n", vector_size(v));
	printf("capacity: %zu\n", vector_capacity(v));
	printf("is_empty: %d\n", vector_is_empty(v));
	vector_push(v, 420);
	printf("at: %d\n", vector_at(v, 0)); // Return 420
	printf("at: %d\n", vector_at(v, 1)); // ERROR
	vector_push(v, 430);
	vector_insert(v, 1, 425);
	vector_push(v, 435);
	vector_push(v, 440);
	vector_push(v, 440);
	vector_push(v, 440);
	vector_push(v, 445);
	vector_push(v, 450);
	printf("at: %d\n", vector_at(v, 1)); // Return 425
	printf("at: %d\n", vector_at(v, 2)); // Return 430

	vector_prepend(v, 415);
	vector_prepend(v, 410);
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity
	for (size_t i = 0; i < v->size; i++)
		printf("%d ", v->array[i]);
	printf("\n");

	printf("pop: %d\n", vector_pop(v));
	printf("pop: %d\n", vector_pop(v));
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity
	for (size_t i = 0; i < v->size; i++)
		printf("%d ", v->array[i]);
	printf("\n");

	vector_delete(v, 1);
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity
	for (size_t i = 0; i < v->size; i++)
		printf("%d ", v->array[i]);
	printf("\n");

	vector_remove(v, 440);
	vector_remove(v, 425);
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity
	for (size_t i = 0; i < v->size; i++)
		printf("%d ", v->array[i]);
	printf("\n");

	printf("find 410: %d\n", vector_find(v, 410));
	printf("find 435: %d\n", vector_find(v, 435));

	vector_resize(v);
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity
	vector_resize(v);
	printf("size: %ld | capacity: 24 + %ld | ", v->size, v->capacity - 24);  // size and capacity

	vector_destroy(v);

	return 0;
}