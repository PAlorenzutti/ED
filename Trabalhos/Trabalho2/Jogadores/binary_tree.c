#include "binary_tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct Node {
    void *key; 
    void *val; 
    struct Node *left;
    struct Node *right;
};

struct BinaryTree {
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

struct KeyValPair{
    void *key;
    void *value;
};

KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *kvp = (KeyValPair *)malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void *key_val_pair_get_key(KeyValPair *kvp) {
    return kvp->key;
}

void *key_val_pair_get_val(KeyValPair *kvp) {
    return kvp->value;
}

void key_val_pair_destroy(KeyValPair *kvp) {
    free(kvp);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    BinaryTree *bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    bt->root = NULL;

    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

Node *treenode_construct(void *key, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->key = key;
    node->val = val;

    node->left = NULL;
    node->right = NULL;

    return node;
}

void treenode_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    if (key_destroy_fn == val_destroy_fn) {
        key_destroy_fn(node->key);
    } else {
        key_destroy_fn(node->key);
        val_destroy_fn(node->val);
    }

    free(node);
}

void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    if (binary_tree_get(bt, key) == NULL) {
        Node *newNode = treenode_construct(key, value);

        if (bt->root == NULL) {
            bt->root = newNode;
        } else {
            Node *current = bt->root;

            while (1) {
                if (bt->cmp_fn(key, current->key) < 0) {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    }

                    current = current->left;
                } else {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    }

                    current = current->right;
                }
            }
        }
    } else {
        bt->key_destroy_fn(key);
        bt->val_destroy_fn(value);
    }
}

Node *binary_tree_add_recursive_helper(Node *node, void *key, void *value, CmpFn cmp_fn) {
    if (node == NULL) {
        return treenode_construct(key, value);
    }
    
    int cmp = cmp_fn(key, node->key);
    if (cmp < 0) {
        node->left = binary_tree_add_recursive_helper(node->left, key, value, cmp_fn);
    } else if (cmp > 0) {
        node->right = binary_tree_add_recursive_helper(node->right, key, value, cmp_fn);
    } else {
        node->val = value;
    }
    return node;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value) {
    bt->root = binary_tree_add_recursive_helper(bt->root, key, value, bt->cmp_fn);
}

void *get_recursive(Node *node, void *key, CmpFn cmp_fn) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = cmp_fn(key, node->key);

    if (cmp == 0) {
        return node->val;
    }

    if (cmp < 0) {
        return get_recursive(node->left, key, cmp_fn);
    } else {
        return get_recursive(node->right, key, cmp_fn);
    }
}

void *binary_tree_get_recursive(BinaryTree *bt, void *key) {
    return get_recursive(bt->root, key, bt->cmp_fn);
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    Node *current = bt->root;

    while (current != NULL) {
        if (!bt->cmp_fn(key, current->key)) {
            return current->val;
        }

        if (bt->cmp_fn(key, current->key) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

Node *find_nearest_recursive(Node *current, void *key, DiffFn diffFn, CmpFn cmp_fn, double *minDiff, Node *nearest)
{
    if (current == NULL || current->val == NULL || current->key == NULL)
        return nearest;

    nearest = find_nearest_recursive(current->left, key, diffFn, cmp_fn, minDiff, nearest);

    if (current != NULL && cmp_fn(key, current->key) != 0){
        double diff = diffFn(key, current->key);

        if (diff < *minDiff){
            *minDiff = diff;
            nearest = current;
        }
    }

    nearest = find_nearest_recursive(current->right, key, diffFn, cmp_fn, minDiff, nearest);

    return nearest;
}

void *binary_tree_get_nearest(BinaryTree *bt, void *key, DiffFn diffFn)
{
    if (!bt || !bt->root){
        return NULL;
    }

    //inicia com a maior diferença possível;
    double minDiff = 1.0;

    Node *nearest = find_nearest_recursive(bt->root, key, diffFn, bt->cmp_fn, &minDiff, NULL);

    return nearest ? nearest->val : NULL;
}

Node *find_min(Node *node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

Node *find_max(Node *node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->right != NULL) {
        node = node->right;
    }

    return node;
}

Node *binary_tree_remove_recursive_helper(Node *node, void *key, CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    if (node == NULL) return NULL;
    
    int cmp = cmp_fn(key, node->key);
    if (cmp < 0) {
        node->left = binary_tree_remove_recursive_helper(node->left, key, cmp_fn, key_destroy_fn, val_destroy_fn);
    } else if (cmp > 0) {
        node->right = binary_tree_remove_recursive_helper(node->right, key, cmp_fn, key_destroy_fn, val_destroy_fn);
    } else {
        if (node->left == NULL) {
            Node *right = node->right;
            // treenode_destroy(node, key_destroy_fn, val_destroy_fn);
            free(node);
            return right;
        } else if (node->right == NULL) {
            Node *left = node->left;
            // treenode_destroy(node, key_destroy_fn, val_destroy_fn);
            free(node);
            return left;
        }
        
        Node *minNode = node->right;
        while (minNode->left != NULL) {
            minNode = minNode->left;
        }
        
        node->key = minNode->key;
        node->val = minNode->val;
        node->right = binary_tree_remove_recursive_helper(node->right, minNode->key, cmp_fn, key_destroy_fn, val_destroy_fn);
    }
    return node;
}

void binary_tree_remove_recursive(BinaryTree *bt, void *key) {
    bt->root = binary_tree_remove_recursive_helper(bt->root, key, bt->cmp_fn, bt->key_destroy_fn, bt->val_destroy_fn);
}

void binary_tree_remove(BinaryTree *bt, void *key) {
    Node *node = bt->root;
    Node *pai = NULL;

    while (node != NULL && bt->cmp_fn(key, node->key) != 0) {
        pai = node;

        if (bt->cmp_fn(key, node->key) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        if (pai == NULL) {
            bt->root = NULL;
        } else if (pai->left == node) {
            pai->left = NULL;
        } else if (pai->right == node) {
            pai->right = NULL;
        }

        free(node);
    }else if (node->left == NULL) {
        if (pai == NULL) {
            bt->root = node->right;
        } else if (pai->left == node) {
            pai->left = node->right;
        } else if (pai->right == node) {
            pai->right = node->right;
        }

        free(node);
    }else if (node->right == NULL) {
        if (pai == NULL) {
            bt->root = node->left;
        } else if (pai->left == node) {
            pai->left = node->left;
        } else if (pai->right == node) {
            pai->right = node->left;
        }

        free(node);
    }else{
        Node *sucessor_pai = node;
        Node *successor = node->right;

        while (successor->left != NULL) {
            sucessor_pai = successor;
            successor = successor->left;
        }

        void *sucessor_key = successor->key;
        void *sucessor_val = successor->val;

        if (sucessor_pai == node) {
            sucessor_pai->right = successor->right;
        } else {
            sucessor_pai->left = successor->right;
        }

        free(successor);

        node->key = sucessor_key;
        node->val = sucessor_val;
    }
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return NULL;
    }

    Node *current = bt->root;
    Node *pai = NULL;

    while (current->left != NULL) {
        pai = current;
        current = current->left;
    }

    KeyValPair *pair = malloc(sizeof(KeyValPair));
    pair->key = current->key;
    pair->value = current->val;

    if (pai == NULL) {
        bt->root = current->right;
    } else {
        pai->left = current->right;
    }

    free(current);

    return pair;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return NULL;
    }

    Node *current = bt->root;
    Node *pai = NULL;

    while (current->right != NULL) {
        pai = current;
        current = current->right;
    }

    KeyValPair *pair = malloc(sizeof(KeyValPair));
    pair->key = current->key;
    pair->value = current->val;

    if (pai == NULL) {
        bt->root = current->left;
    } else {
        pai->right = current->left;
    }

    free(current);

    return pair;
}

void *binary_tree_min(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return NULL;
    }

    Node *current = bt->root;

    while (current->left != NULL) {
        current = current->left;
    }

    return current->val;
}

void *binary_tree_max(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return NULL;
    }

    Node *current = bt->root;

    while (current->right != NULL) {
        current = current->right;
    }

    return current->val;
}

int binary_tree_empty(BinaryTree *bt) {
    return bt->root == NULL;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return vector_construct(); 
    }

    Vector *output = vector_construct(); 
    Vector *queue = vector_construct(); 
    vector_push_back(queue, bt->root); 

    while (vector_size(queue) > 0) {
        Node *current = vector_pop_front(queue); 

        KeyValPair *kvp = key_val_pair_construct(current->key, current->val);
        vector_push_back(output, kvp);

        if (current->left != NULL) {
            vector_push_back(queue, current->left);
        }
        if (current->right != NULL) {
            vector_push_back(queue, current->right);
        }
    }

    vector_destroy(queue);
    return output;
}

void inorder_recursive(Node *node, Vector *v) {
    if (node == NULL) return;
    inorder_recursive(node->left, v); 
    KeyValPair *kvp = key_val_pair_construct(node->key, node->val);
    vector_push_back(v, kvp); 
    inorder_recursive(node->right, v); 
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt) {
    Vector *v = vector_construct();
    if (bt != NULL && bt->root != NULL) {
        inorder_recursive(bt->root, v);
    }
    return v;
}

void preorder_recursive(Node *node, Vector *v) {
    if (node == NULL) return;
    KeyValPair *kvp = key_val_pair_construct(node->key, node->val);
    vector_push_back(v, kvp); 
    preorder_recursive(node->left, v); 
    preorder_recursive(node->right, v); 
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Vector *v = vector_construct();
    if (bt != NULL && bt->root != NULL) {
        preorder_recursive(bt->root, v);
    }
    return v;
}

void postorder_recursive(Node *node, Vector *v) {
    if (node == NULL) return;
    postorder_recursive(node->left, v); 
    postorder_recursive(node->right, v); 
    KeyValPair *kvp = key_val_pair_construct(node->key, node->val);
    vector_push_back(v, kvp); 
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Vector *v = vector_construct();

    if (bt != NULL && bt->root != NULL) {
        postorder_recursive(bt->root, v);
    }

    return v;
}

void destroy_recursive(BinaryTree *bt, Node *node) {
    if (node == NULL) {
        return;
    }

    destroy_recursive(bt, node->left);

    destroy_recursive(bt, node->right);

    treenode_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
}

void binary_tree_destroy(BinaryTree *bt) {
    if (bt == NULL) return;

    destroy_recursive(bt, bt->root);

    free(bt);
}

void print_recursive(Node *node, PrintFn printFn) {
    if (node == NULL) {
        printf("NULL");
        return;
    }

    printf("(");
    printFn(node->key);
    print_recursive(node->left, printFn);
    printf(", ");
    print_recursive(node->right, printFn);
    printf(")");
}

void binary_tree_print(BinaryTree *bt, PrintFn printFn) {
    if (bt == NULL) return;
    print_recursive(bt->root, printFn);
    printf("\n");
}
