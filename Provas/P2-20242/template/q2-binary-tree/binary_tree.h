
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_construct();
void binary_tree_destroy(BinaryTree *bt);
void binary_tree_add(BinaryTree *bt, int value);
int *binary_tree_knn(BinaryTree *bt, int x, int k, int min, int max, int *out_array_size);

#endif