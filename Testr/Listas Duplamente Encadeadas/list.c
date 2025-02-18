#include "list.h"

#include <stdlib.h>
#include <stdio.h>

List *list_construct(){
    List *l = malloc(sizeof(List));

    l->head = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

int list_size(List *l){
    return l->size;
}

void list_push_front(List *l, data_type data){
    Node *new_node = node_construct(data, NULL, l->head);

    if (l->head != NULL) {
        l->head->prev = new_node;
    } else {
        l->last = new_node; // Set last when list is empty
    }

    l->head = new_node;
    l->size++;
}

void list_push_back(List *l, data_type data){
    Node *new_node = node_construct(data, l->last, NULL);

    //se tiver nenhum nó na lista
    if(l->last == NULL){
        //atualiza o último como ele mesmo;
        l->head = l->last = new_node;
    }else{
        //atualiza o next do atual último;
        l->last->next = new_node;

        //atualiza o último de fato;
        l->last = new_node;
    }   

    l->size++;
}

data_type list_pop_back(List *l) {
    data_type data = l->last->value;
    Node *old = l->last;

    if (l->size == 1) {
        l->head = NULL;
        l->last = NULL;
    } else {
        l->last = old->prev;
        l->last->next = NULL;
    }

    node_destroy(old);
    l->size--;

    return data;
}

data_type list_pop_front(List *l) {
    data_type data = l->head->value;
    Node *old = l->head;

    if (l->size == 1) {
        l->head = NULL;
        l->last = NULL;
    } else {
        l->head = old->next;
        l->head->prev = NULL;
    }

    node_destroy(old);
    l->size--;

    return data;
}

void list_print(List *l, void (*print_fn)(data_type)){
    Node *iterator = l->head;

    printf("[");

    while(iterator != NULL){
        node_print(iterator, print_fn);

        if(iterator->next != NULL){
            printf(", ");
        }

        iterator = iterator->next;
    }

    printf("]");
}

void list_print_reverse(List *l, void (*print_fn)(data_type)){
    Node *iterator = l->last;

    printf("[");

    while(iterator != NULL){
        node_print(iterator, print_fn);

        if(iterator->prev != NULL){
            printf(", ");
        }

        iterator = iterator->prev;
    }

    printf("]");
}


void list_destroy(List *l){
    while(l->head != NULL){
        Node *n = l->head;
        l->head = l->head->next;
        node_destroy(n);
    }

    free(l);
}

ListIterator *list_front_iterator(List *l){
    ListIterator *it = malloc(sizeof(ListIterator));

    it->current = l->head;

    return it;
}

ListIterator *list_back_iterator(List *l){
    ListIterator *it = malloc(sizeof(ListIterator));

    it->current = l->last;

    return it;
}

bool list_iterator_is_over(ListIterator *it){
    return (it->current == NULL);
}

data_type *list_iterator_previous(ListIterator *it){
    data_type *data = &(it->current->value);

    it->current = it->current->prev;

    return data;
}

data_type *list_iterator_next(ListIterator *it){
    data_type *data = &(it->current->value);

    it->current = it->current->next;

    return data;
}

void list_iterator_destroy(ListIterator *it){
    free(it);
}
