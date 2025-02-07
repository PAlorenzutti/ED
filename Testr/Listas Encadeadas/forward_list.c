#include "forward_list.h"

#include <stdio.h>
#include <stdlib.h>

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));

    l->size = 0;
    l->head = NULL;
    l->last = NULL;

    return l;
}

void forward_list_push_front(ForwardList *l, data_type data){
    //cria um novo nó com próximo com a cabeça antiga e torna esse a atual cabeça
    l->head = node_construct(data, l->head);
    l->size++;

    if(l->size == 1){
        l->last = l->head;
    }
}

void forward_list_push_back(ForwardList *l, data_type data){
    //cria um novo nó apontando pra NULL;
    //faz o antigo apontar pro novo final

    Node *n = node_construct(data, NULL);

    if(l->last == NULL){
        l->head = l->last = n;
    }else{
        l->last->next = n;
        l->last = n;
    }

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
            printf("\n"); 
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

    // l->head = node_next(l->head);
    l->head = l->head->next;

    data_type value = prev->value;

    node_destroy(prev);

    l->size--;

    if(l->size <= 1){
        l->last = l->head;
    }

    return value;
}

data_type forward_list_pop_index(ForwardList *l, int index) {
    if (index < 0 || index >= forward_list_size(l)) {
        printf("INVALID INDEX\n");
        return NULL;
    }

    Node *n = l->head;
    Node *prev = NULL;

    for (int count = 0; count < index; count++) {
        prev = n;
        n = n->next;
    }

    if (prev == NULL) {
        l->head = n->next; // Remove o primeiro elemento
    } else {
        prev->next = n->next;
    }

    // Atualiza o ponteiro 'last' se o nó removido era o último
    if (n == l->last) {
        l->last = prev; // Se prev for NULL, a lista está vazia
    }

    data_type val = n->value;
    node_destroy(n);
    l->size--;

    return val;
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    //pega a cabeça do m;
    Node *n = m->head;

    while(n != NULL){
        forward_list_push_front(l, n->value);

        n = node_next(n);
    }
}

void forward_list_clear(ForwardList *l){
    //pega um nó
    //destrói esse nó
    //diminui o tamanho da lista;

    //se o próximo não for null;
    //passa pro próximo

    Node *n = l->head;

    while(n != NULL){
        Node *temp = n;

        n = node_next(n);

        node_destroy(temp);

        l->size--;
    }
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *l2 = forward_list_construct();

    while(l->head != NULL){
        data_type temp = forward_list_pop_front(l);

        forward_list_push_front(l2, temp);
    }

    return l2;
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