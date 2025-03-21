
#include <stdio.h>
#include <stdlib.h>

#include "forward_list.h"

FlNode *node_construct(data_type value, FlNode *next)
{
    FlNode *n = (FlNode *)malloc(sizeof(FlNode));
    n->value = value;
    n->next = next;
    return n;
}

void node_destroy(FlNode *n)
{
    free(n);
}

ForwardList *forward_list_construct()
{
    ForwardList *l = (ForwardList *)calloc(1, sizeof(ForwardList));

    l->head = NULL;
    l->size = 0;

    return l;
}

void forward_list_push_front(ForwardList *l, data_type data)
{
    l->head = node_construct(data, l->head);
    l->size++;
}

int forward_list_size(ForwardList *l)
{
    return l->size;
}

data_type forward_list_pop_front(ForwardList *l)
{
    if (l->head == NULL)
        exit(printf("Error: forward_list_pop_front(): list is empty."));

    FlNode *n = l->head;
    l->head = l->head->next;
    data_type data = n->value;
    node_destroy(n);
    l->size--;
    return data;
}

void forward_list_destroy(ForwardList *l)
{
    FlNode *n = l->head;
    while (n != NULL)
    {
        FlNode *next = n->next;
        node_destroy(n);
        n = next;
    }

    free(l);
}


