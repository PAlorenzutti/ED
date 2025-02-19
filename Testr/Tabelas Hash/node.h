#ifndef _NODE_H_
#define _NODE_H_

typedef void* data_type;

typedef struct Node
{
    data_type value;
    struct Node *next;
} Node;

Node *node_construct(data_type value, Node *next);

data_type node_value(Node *node);

Node *node_next(Node *node);

int node_compare(Node *n1, Node *n2, int (*comp_fn) (void*, void*));

void node_destroy(Node *n);

#endif