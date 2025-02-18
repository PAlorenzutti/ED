#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

struct Queue{
    List *l;
};

// cria uma queue
Queue *queue_construct(){
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    queue->l = list_construct();

    return queue;
}

// insere um item na queue 
void queue_enqueue(Queue *queue, data_type value){
    list_push_back(queue->l, value);
}

// remove o elemento mais antigo da pilha e o retorna
data_type queue_dequeue(Queue *queue){
    return list_pop_front(queue->l); // Remove o item da fila
}

// retorna 1 se a queue está vazia e 0 caso contrário
int queue_empty(Queue *queue){
    if(!list_size(queue->l)){
        return 1;
    }else{
        return 0;
    }
}

int queue_size(Queue *queue){
    return list_size(queue->l);
}

// libera o espaco alocado para a queue
void queue_destroy(Queue *queue){
    list_destroy(queue->l);
    free(queue); // Libera a fila
}