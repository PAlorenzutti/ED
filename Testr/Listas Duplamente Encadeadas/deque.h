
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "list.h"

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back(Deque *f, data_type item);
void deque_push_front(Deque *f, data_type item);
data_type deque_pop_back(Deque *f);
data_type deque_pop_front(Deque *f);
void deque_destroy(Deque *f);

#endif