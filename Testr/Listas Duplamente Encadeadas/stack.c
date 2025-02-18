#include "stack.h"
#include "list.h"

#include <stdlib.h>

struct Stack{
    List *l;
};

// cria uma stack
Stack *stack_construct(){
    Stack *s = malloc(sizeof(Stack));

    s->l = list_construct();

    return s;
}

// insere um item na stack
void stack_push(Stack *s, data_type val){
    list_push_back(s->l, val);
}

// remove o ultimo item inserido e o retorna
data_type stack_pop(Stack *s){
    return list_pop_back(s->l);
}

int stack_size(Stack *s){
    return list_size(s->l);
}

// retorna 1 se a stack está vazia e 0 caso contrário
int stack_empty(Stack *s){
    if(list_size(s->l) > 0){
        return 0;
    }else{
        return 1;
    }
}

// libera o espaço alocado para a stack
void stack_destroy(Stack *s){
    list_destroy(s->l);
    free(s);
}