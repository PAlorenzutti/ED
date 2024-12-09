#include "deque.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4

struct Deque{
    int *v;         // Array para armazenar os dados
    int size;       // Quantidade de elementos na deque
    int allocated;  // Capacidade total do array
    int start;      // Índice do início do deque
    int end;        // Índice do final do deque
};

Deque *deque_construct() {
    Deque *f = (Deque *)malloc(sizeof(Deque));
    f->v = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    f->size = 0;
    f->allocated = INITIAL_CAPACITY;
    f->start = 0;
    f->end = 0;
    return f;
}

void deque_resize(Deque *f) {
    int new_capacity = f->allocated * 2;
    int *new_v = (int *)malloc(new_capacity * sizeof(int));

    // Realoca os elementos existentes na nova ordem circular
    for (int i = 0; i < f->size; i++) {
        new_v[i] = f->v[(f->start + i) % f->allocated];
    }

    free(f->v);
    f->v = new_v;
    f->allocated = new_capacity;
    f->start = 0;
    f->end = f->size;
}

void deque_push_back(Deque *f, int item) {
    // Redimensiona se não houver espaço
    if (f->size == f->allocated) {
        deque_resize(f);
    }

    // Insere o item no final
    f->v[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void deque_push_front(Deque *f, int item) {
    // Redimensiona se não houver espaço
    if (f->size == f->allocated) {
        deque_resize(f);
    }

    // Ajusta o índice do início e insere o item
    f->start = (f->start - 1 + f->allocated) % f->allocated;
    f->v[f->start] = item;
    f->size++;
}

int deque_pop_back(Deque *f) {
    if (f->size == 0) {
        printf("Deque vazio!\n");
        exit(1);
    }

    // Ajusta o índice do final
    f->end = (f->end - 1 + f->allocated) % f->allocated;
    int item = f->v[f->end];
    f->size--;
    return item;
}

int deque_pop_front(Deque *f) {
    if (f->size == 0) {
        printf("Deque vazio!\n");
        exit(1);
    }

    // Remove o item do início e ajusta o índice
    int item = f->v[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return item;
}

void deque_destroy(Deque *f) {
    free(f->v);
    free(f);
}