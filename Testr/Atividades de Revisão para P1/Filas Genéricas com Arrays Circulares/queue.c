#include "queue.h"

#include <stdlib.h>

struct Queue{
    void **data;
    int size;
    int allocated;
    int start;
    int end;
};

// Create an queue
Queue *queue_constructor(int max_capacity){
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    queue->allocated = max_capacity;
    queue->data = (void**)malloc(sizeof(void*) * queue->allocated);

    queue->size = 0;
    queue->start = 0;
    queue->end = 0;

    return queue;
}

// Add an element
void queue_add(Queue *queue, void *data){
    //adiciona elemento ao final da lista;
    queue->data[queue->end] = data;

    //incrementa o tamanho da lista;
    queue->size++;

    //atualiza o final da lista;
    queue->end = (queue->end + 1) % queue->allocated;
}

// Remove the oldest element in the queue
void* queue_remove(Queue *queue){
    //remove o primeiro elemento da lista;
    void *data = queue->data[queue->start];

    //decrementa o tamanho da lista;
    queue->size--;

    //atualiza o início da lista;
    queue->start = (queue->start + 1) % queue->allocated;

    return data;
}

// Return the number of elements in the queue
int queue_size(Queue *queue){
    return queue->size;
}

// Return 1 if the queue is full and 0, otherwise
int queue_is_full(Queue *queue){
    if(queue->size == queue->allocated){
        return 1;
    }else{
        return 0;
    }
}

// Return 1 if the queue is empty and 0, otherwise
int queue_is_empty(Queue *queue){
    if(queue->size == 0){
        return 1;
    }else{
        return 0;
    }
}

// Free the data structure.
// IMPORTANT: the user of the lib is responsible for removing and freeing elements
// remaining in the queue. In the queue is not empty when the functions is called,
// the function will not release them.
void queue_destroy(Queue *queue){
    free(queue->data);
    free(queue);
}