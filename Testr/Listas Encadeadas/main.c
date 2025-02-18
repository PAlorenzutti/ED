
#include <stdio.h>
#include <stdlib.h>

#include "forward_list.h"

void print_data(data_type data){
// implemente a funcao para mostrar um elemento da lista na tela.
    int *inteiro = (int*)data;

    printf("%d", *inteiro);
}

int compare_data(data_type d1, data_type d2){
    int *i1 = (int*)d1;
    int *i2 = (int*)d2;

    if(*i1 > *i2){
        return 1;
    }

    if(*i1 < *i2){
        return -1;
    }

    return 0;
}

int main()
{
    int num_elements;
    scanf("%d\n", &num_elements);

    ForwardList *list = forward_list_construct();

    for(int i = 0; i < num_elements; i++){
        int *value = malloc(sizeof(int));
        scanf("%d\n", value);

        forward_list_push_back(list, value);
    }

    forward_list_sort(list, compare_data);

    forward_list_print(list, print_data);

    forward_list_destroy(list);

    return 0;
}
