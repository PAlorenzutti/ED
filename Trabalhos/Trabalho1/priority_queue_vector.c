#include "priority_queue_vector.h"
#include "vector.h"

#include <stdlib.h>

struct PriorityQueue{
    Vector *v;
    int (*cmp_fn)(const void *, const void *);
};

PriorityQueue *pq_constructor(int (*cmp_fn)(const void *, const void *)){
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));

   pq->v = vector_construct();
   pq->cmp_fn = cmp_fn;

   return pq;
}

void pq_push(PriorityQueue *pq, void *data){
    //insere o vetor ao final da fila
    vector_push_back(pq->v, data);

    //ordena o vetor para ficar em ordem de prioridade
    vector_sort(pq->v, pq->cmp_fn);
}

void *pq_pop(PriorityQueue *pq){
    return vector_pop_back(pq->v);
}

int pq_size(PriorityQueue *pq){
    return vector_size(pq->v);
}   

void pq_destroy(PriorityQueue *pq){
    vector_destroy(pq->v);
    free(pq);
}
