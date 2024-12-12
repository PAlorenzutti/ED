#include "deque.h"

#include <stdlib.h>
#include <stdio.h>

typedef void* data_type;

#define INITIAL_CAPACITY 10

struct Deque{
    data_type *v;   // Array para armazenar os dados
    int size;       // Quantidade de elementos na deque
    int allocated;  // Capacidade total do array
    int start;      // Índice do início do deque
    int end;        // Índice do final do deque
};

Deque *deque_construct() {
    Deque *f = (Deque *)malloc(sizeof(Deque));

    f->v = (data_type*)malloc(INITIAL_CAPACITY * sizeof(data_type));

    f->size = 0;
    f->allocated = INITIAL_CAPACITY;
    f->start = 0;
    f->end = 0;

    return f;
}

void deque_resize(Deque *f) {
    //dobra a capacidade do vetor antigo
    int new_capacity = f->allocated * 2;
    data_type *new_v = (data_type*)malloc(new_capacity * sizeof(data_type));

    //realoca os elementos existentes na nova ordem circular
    for (int i = 0; i < f->size; i++) {
        new_v[i] = f->v[(f->start + i) % f->allocated];
    }

    //desaloca o vetor antigo;
    free(f->v);
    
    //atribui o vetor novo ao deque;
    f->v = new_v;
    f->allocated = new_capacity;
    f->start = 0;
    f->end = f->size;
}

void deque_push_back(Deque *f, data_type item) {
    //redimensiona se não houver espaço
    if (f->size == f->allocated) {
        deque_resize(f);
    }

    //insere o item no final e depois ajusta
    f->v[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void deque_push_front(Deque *f, data_type item) {
    //redimensiona se não houver espaço
    if (f->size == f->allocated) {
        deque_resize(f);
    }

    //ajusta o índice do início e insere o item
    f->start = (f->start - 1 + f->allocated) % f->allocated;
    f->v[f->start] = item;
    f->size++;
}

data_type deque_pop_back(Deque *f){
    //ajusta o índice do final e remove o item
    f->end = (f->end - 1 + f->allocated) % f->allocated;
    data_type item = f->v[f->end];
    f->size--;

    return item;
}

data_type deque_pop_front(Deque *f) {
    //remove o item do início e ajusta o índice
    data_type item = f->v[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;

    return item;
}

data_type deque_get(Deque *f, int idx){
    return f->v[(f->start + idx) % f->allocated];
}

int deque_size(Deque *f){
    return f->size;
}

void deque_destroy(Deque *f) {
    for(int i = 0; i < f->size; i++){
        free(deque_pop_front(f));
    }
    
    free(f->v);
    free(f);
}