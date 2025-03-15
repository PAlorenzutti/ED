#include "binary_tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    KeyValPair *kvp;
    struct Node *left;
    struct Node *right;
}Node;

struct BinaryTree{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    KeyDestroyFn val_destroy_fn;
};

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *bt = (BinaryTree*)malloc(sizeof(BinaryTree));

    //inicia a raiz da árvore como nula;
    bt->root = NULL;

    //passa as funções de comparação e destruição para a árvore;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

//supondo sempre um nó novo;
Node *node_construct(void *key, void *val){
    Node *node = (Node*)malloc(sizeof(Node));

    //cria o par e adicionar o par ao nó;
    KeyValPair *kvp = key_val_pair_construct(key, val);
    node->kvp = kvp;  

    //inicia os filhos do nó como NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = (KeyValPair*)malloc(sizeof(KeyValPair));

    //passa chave e valor para o par;
    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void *key_val_pair_get_key(KeyValPair *kvp){
    return kvp->key;
}

void *key_val_pair_get_val(KeyValPair *kvp){
    return kvp->value;
}

void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}

Node *add_recursive(Node *node, void *key, void *value, CmpFn cmp_fn){
    //se o nó for null, significa que ele chegou ao final de algum ramo, portanto cria ele como se fosse o último;
    if (node == NULL){
        return node_construct(key, value);
    }

    //se a chave tiver um valor menor, insere à esquerda recursivamente;
    //se a chave tiver um valor maior, insere à direita recursivamente;
    if (cmp_fn(key, key_val_pair_get_key(node->kvp)) < 0){
        node->left = add_recursive(node->left, key, value, cmp_fn);
    }else{
        node->right = add_recursive(node->right, key, value, cmp_fn);
    }

    return node;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value) {
    if (bt == NULL) return;
    bt->root = add_recursive(bt->root, key, value, bt->cmp_fn);
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    //cria um novo nó;
    Node *novo = node_construct(key, value);

    //se a cabeça for null, significa que a árvore está vazia, e o nó a ser adicionado é a nova cabeça
    if(bt->root == NULL){
        bt->root = novo;
        return;
    }

    Node *atual = bt->root;

    while(true){
        //se ele for menor ou igual ao nó atual, vai pra esquerda;
        if(bt->cmp_fn(key, key_val_pair_get_key(atual->kvp)) <= 0){
            //se o nó da esquerda, não existir, ele é o novo nó da esquerda;
            if(atual->left == NULL){
                atual->left = novo;
                break;
            }else{
                //se o nó existir, continua percorrendo a esquerda até não existir;
                atual = atual->left;
            }
        }else{
            //se ele for maior, vai pra direita;
            
            //se o da direita for igual a NULL, ele será o novo nó da direita;
            if(atual->right == NULL){
                atual->right = novo;
                break;
            }else{
                atual = atual->right;
            }
        }
    }
}

void *get_recursive(Node *node, void *key, CmpFn cmp_fn) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = cmp_fn(key, key_val_pair_get_key(node->kvp));

    if (cmp == 0) {
        return key_val_pair_get_val(node->kvp);
    }

    if (cmp < 0) {
        return get_recursive(node->left, key, cmp_fn);
    } else {
        return get_recursive(node->right, key, cmp_fn);
    }
}


void *binary_tree_get_recursive(BinaryTree *bt, void *key){
    //começa a pesquisar pela raiz e retorna o que for achado (se for);
    return get_recursive(bt->root, key, bt->cmp_fn);
}

void *binary_tree_get(BinaryTree *bt, void *key){
    //inicia a busca pela cabeça;
    Node *atual = bt->root;

    while(atual != NULL){
        //se for igual, retorna o valor;
        if(!bt->cmp_fn(key, key_val_pair_get_key(atual->kvp))){
            return key_val_pair_get_val(atual->kvp);
        }

        //se for menor, vai pra esquerda;
        if(bt->cmp_fn(key, key_val_pair_get_key(atual->kvp)) < 0){
            atual = atual->left;
        }else{
            //se for maior, vai pra direita;
            atual = atual->right;
        }
    }

    return NULL;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    //destrói a chave e o valor;
    key_destroy_fn(node->kvp->key);
    val_destroy_fn(node->kvp->value);

    //destrói o par;
    key_val_pair_destroy(node->kvp);

    //destrói o nó;
    free(node);
}

int binary_tree_empty(BinaryTree *bt){
    return bt->root == NULL;
}

void binary_tree_destroy_recursive(BinaryTree *bt, Node *node){
    //se o nó já estiver vazio, sai (já encerrou o ramo por aqui);
    if(node == NULL){
        return;
    }

    //se não retornou, tenta avançar ainda mais pra esquerda;
    binary_tree_destroy_recursive(bt, node->left);

    //depois, quando concluído os filhos da esquerda, vai pro da direita;
    binary_tree_destroy_recursive(bt, node->right);

    //destrói o nó
    node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
}

void binary_tree_destroy(BinaryTree *bt) {
    if (bt == NULL) return;

    // Libera todos os nós da árvore
    binary_tree_destroy_recursive(bt, bt->root);

    // Libera a estrutura da árvore
    free(bt);
}

void binary_tree_print_recursive(Node *node) {
    if (node == NULL) {
        return;
    }

    binary_tree_print_recursive(node->left);
    printf("%d ", *(int *)key_val_pair_get_key(node->kvp));
    binary_tree_print_recursive(node->right);
}

void binary_tree_print(BinaryTree *bt) {
    if (bt == NULL) return;
    binary_tree_print_recursive(bt->root);
    printf("\n");
}