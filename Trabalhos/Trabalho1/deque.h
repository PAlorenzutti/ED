#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "vector.h"

typedef struct Deque Deque;

Deque *deque_construct();

void deque_push_back(Deque *f, data_type item);

void deque_push_front(Deque *f, data_type item);

data_type deque_pop_back(Deque *f);

data_type deque_pop_front(Deque *f);

data_type deque_get(Deque *f, int idx);

data_type deque_min(Deque *f, int (*cmp_fn) (const void *, const void *));

int deque_size(Deque *f);

void deque_sort(Deque *f, int (*cmp_fn) (const void *, const void *));

void deque_swap(Deque *f, int i, int j);

void deque_destroy(Deque *f);

#endif