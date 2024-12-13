#ifndef _HEAP_H_
#define _HEAP_H_

#include "vector.h"

typedef int (*CmpFn)(const void *, const void *); 

typedef struct Heap Heap;

Heap *heap_constructor(CmpFn cmp_fn);

void heap_push(Heap *heap, data_type data); 

void heap_heapify_up(Vector *nodes, int idx, CmpFn cmp_fn);

void heap_heapify_down(Vector *nodes, int size, int idx, CmpFn cmp_fn);

int heap_empty(Heap *heap);

int heap_size(Heap *heap);

data_type heap_get(Heap *heap, int idx);

data_type heap_max(Heap *heap);

data_type heap_pop(Heap *heap); 

void heap_destroy(Heap *heap);

void heap_sort(Vector *v, int cmp_fn(const void *, const void *));


#endif