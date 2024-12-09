#include "deque.h"

#include <stdio.h>
#include <string.h>

void perform_operation(Deque *f){
    char operacao[32];
    scanf("%s", operacao);

    if(!strcmp(operacao, "PUSH_BACK")){
        int item;
        scanf(" %d\n", &item);
        deque_push_back(f, item);
    }

    if(!strcmp(operacao, "PUSH_FRONT")){
        int item;
        scanf(" %d\n", &item);
        deque_push_front(f, item);
    }

    if(!strcmp(operacao, "POP_BACK")){
        int data = deque_pop_back(f);

        printf("%d\n", data);
    }

    if(!strcmp(operacao, "POP_FRONT")){
        int data = deque_pop_front(f);

        printf("%d\n", data);
    }
}

int main(){
    Deque *f = deque_construct();
    
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        perform_operation(f);
    }

    deque_destroy(f);
}
