#include "vector.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_OPERATION 8

void perform_operation(Stack *stack){
    char operation[TAM_OPERATION];
    scanf("%s", operation);

    if(!strcmp(operation, "PUSH")){
        char *data = (char*)malloc(sizeof(char) * TAM_MAX_DATA);
        scanf(" %s\n", data);

        stack_push(stack, data);
    }

    if(!strcmp(operation, "POP")){
        data_type data = stack_pop(stack);
        printf("%s\n", (char*)data);
        free(data);
    }
}

int main(){
    Stack *stack = stack_construct();

    int n;
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        perform_operation(stack);
    }
    
    stack_destroy(stack);
}