#include "deque.h"
#include "list.h"

#include <stdlib.h>

struct Deque{
    List *l;
};

Deque *deque_construct(){
    Deque *f = malloc(sizeof(Deque));

    f->l = list_construct();

    return f;
}
void deque_push_back(Deque *f, data_type item){
    list_push_back(f->l, item);
}

void deque_push_front(Deque *f, data_type item){
    list_push_front(f->l, item);
}
data_type deque_pop_back(Deque *f){
    return list_pop_back(f->l);
}   

data_type deque_pop_front(Deque *f){
    return list_pop_front(f->l);
}

void deque_destroy(Deque *f){
    list_destroy(f->l);
    free(f);
}