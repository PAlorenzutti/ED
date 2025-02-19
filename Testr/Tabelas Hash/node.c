#include "node.h"

#include <stdlib.h>

Node *node_construct(data_type value, Node *next){
  Node *node = (Node*)malloc(sizeof(Node));

  node->value = value;
  node->next = next;

  return node;
}

data_type node_value(Node *node){
  return node->value;
}

Node* node_next(Node *node){
  return node->next;
}

int node_compare(Node *n1, Node *n2, int (*comp_fn) (void*, void*)){
  return comp_fn(n1->value, n2->value);
}

void node_destroy(Node *node){
  free(node);
}