#include "forward_list.h"

#include <stdio.h>
#include <stdlib.h>

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->size = 0;
    l->head = NULL;

    return l;
}

void forward_list_push_front(ForwardList *l, data_type data){
    //cria um novo nó com próximo com a cabeça antiga e torna esse a atual cabeça
    l->head = node_construct(data, l->head);

    l->size++;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    //pega o endereço do primeiro nó (cabeça);
    Node *n = l->head;

    printf("["); 
    
    while (n != NULL) {
        print_fn(n->value);

        if (n->next != NULL) {
            printf(", "); 
        }

        n = n->next;
    }
    
    printf("]"); 
}

data_type forward_list_get(ForwardList *l, int i){
    if(i < 0 || i >= l->size){
        printf("Error: forward_list_get");
        exit(1);
    }

    Node *n = l->head;

    for(int j = 0; n != NULL && j < i; j++){
        n = node_next(n);
    }

    return n->value;
}

data_type forward_list_pop_front(ForwardList *l){
    if(l->head == NULL){
        printf("Error: forward_list_pop_front");
    }

    Node *prev = l->head;

    l->head = node_next(l->head);

    data_type value = prev->value;

    node_destroy(prev);

    return value;
}

data_type forward_list_pop_index(ForwardList *l, int index){
    if(index < 0 || index >= forward_list_size(l)){
        printf("Error: Invalid index '%d'.\n", index);
    }

    Node *n = l->head;
    Node *prev = NULL;

    for(int count = 0; count < index; count++){
        prev = n;
        n = n->next;
    }

    //para o caso especial de índice 0;
    if(prev == NULL){
        l->head = n->next;
    }else{
        //o anterior aponta pro próximo do atual;
        prev->next = n->next;
    }

    data_type val = n->value;

    //destrói o atual;
    node_destroy(n);

    l->size--;

    return val;
}

void forward_list_remove(ForwardList *l, data_type val){
    Node *n = l->head;
    Node *prev = NULL;

    while (n != NULL) {
        if (node_value(n) == val) {
            Node *temp = n;
            
            if (prev == NULL){
                l->head = n->next;
            }else{
                prev->next = n->next;
            }
            
            n = n->next;
            node_destroy(temp);
            l->size--;
        }else{
            prev = n;
            n = n->next;
        }
    }
}

void forward_list_destroy(ForwardList *l){
    while(l->head != NULL){
        Node *n = l->head;
        l->head = node_next(l->head);
        node_destroy(n);
    }

    free(l);
}