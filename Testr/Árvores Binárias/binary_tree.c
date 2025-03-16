#include "binary_tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    void *key;  // Chave do nó
    void *val;  // Valor do nó
    struct Node *left;
    struct Node *right;
} Node;

struct BinaryTree {
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = (KeyValPair *)malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    BinaryTree *bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    // Inicia a raiz da árvore como nula
    bt->root = NULL;

    // Passa as funções de comparação e destruição para a árvore
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

// Supondo sempre um nó novo
Node *node_construct(void *key, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));

    // Inicializa a chave e o valor do nó
    node->key = key;
    node->val = val;

    // Inicia os filhos do nó como NULL
    node->left = NULL;
    node->right = NULL;

    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    // Destrói a chave e o valor
    key_destroy_fn(node->key);
    val_destroy_fn(node->val);

    // Destrói o nó
    free(node);
}

void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    if(binary_tree_get(bt, key) == NULL){
        Node *novo = node_construct(key, value);

        if(bt->root == NULL){
            bt->root = novo;
        }else{
            Node *atual = bt->root;

            while(1){
                if(bt->cmp_fn(key, atual->key) < 0){
                    if(atual->left == NULL){
                        atual->left = novo;
                        break;
                    }

                    atual = atual->left;
                }else{
                    if(atual->right == NULL){
                        atual->right = novo;
                        break;
                    }

                    atual = atual->right;
                }
            }
        }
    }else{
        bt->key_destroy_fn(key);
        bt->val_destroy_fn(value);
    }
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
    // Começa a pesquisar pela raiz e retorna o que for achado (se for)
    return get_recursive(bt->root, key, bt->cmp_fn);
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    // Inicia a busca pela raiz
    Node *atual = bt->root;

    while (atual != NULL) {
        // Se for igual, retorna o valor
        if (!bt->cmp_fn(key, atual->key)) {
            return atual->val;
        }

        // Se for menor, vai pra esquerda
        if (bt->cmp_fn(key, atual->key) < 0) {
            atual = atual->left;
        } else {
            // Se for maior, vai pra direita
            atual = atual->right;
        }
    }

    return NULL;
}

//encontrar o mínimo a partir de um nó
Node *find_min(Node *node) {
    if (node == NULL) {
        return NULL;
    }

    //para achar o mínimo do ramo, tem de percorrer até a direita o quanto der
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

//encontrar o máximo a partir de um nó
Node *find_max(Node *node){
    if(node == NULL){
        return NULL;
    }

    //enquanto o próximo nó maior (da direita) existir, continua indo pra direita;
    while(node->right != NULL){
        node = node->right;
    }

    return node;
}

void binary_tree_remove(BinaryTree *bt, void *key) {  
    //assume o nó a ser removido como a raiz;
    Node *node = bt->root;
    Node *pai = NULL;

    //procura o nó que vai ser removido de fato;
    while(node != NULL && bt->cmp_fn(key, node->key) != 0){
        pai = node;

        if(bt->cmp_fn(key, node->key) < 0){
            node = node->left;
        } else {
            node = node->right;
        }
    }

    //se não encontrar, apenas sai da função;
    if(node == NULL){
        return;
    }

    //caso 1: nó folha (não tem filhos)
    if(node->left == NULL && node->right == NULL){
        //se o pai for NULL, significa que é a raiz;
        if(pai == NULL){
            //atualiza a raiz para NULL;
            bt->root = NULL;
        //se não, verifica se é o filho da esquerda ou direita;
        }else if(pai->left == node){
            //atualiza o filho da esquerda do pai do nó a ser removido como NULL;
            pai->left = NULL;
        }else if(pai->right == node){
            //atualiza o filho da direita do pai do nó a ser removido como NULL;
            pai->right = NULL;
        }

        node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
    }
    // Caso 2: nó com apenas um filho à direita
    else if (node->left == NULL) {
        // Se o pai for NULL, significa que é a raiz
        if (pai == NULL) {
            // Atualiza a raiz para o filho da direita
            bt->root = node->right;
        } else if (pai->left == node) {
            // Se o nó a ser removido for o filho esquerdo do pai, atualiza o filho esquerdo do pai
            pai->left = node->right;
        } else if (pai->right == node) {
            // Se o nó a ser removido for o filho direito do pai, atualiza o filho direito do pai
            pai->right = node->right;
        }

        node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
    }
    // Caso 3: nó com apenas um filho à esquerda
    else if (node->right == NULL) {
        // Se o pai for NULL, significa que é a raiz
        if (pai == NULL) {
            // Atualiza a raiz para o filho da esquerda
            bt->root = node->left;
        } else if (pai->left == node) {
            // Se o nó a ser removido for o filho esquerdo do pai, atualiza o filho esquerdo do pai
            pai->left = node->left;
        } else if (pai->right == node) {
            // Se o nó a ser removido for o filho direito do pai, atualiza o filho direito do pai
            pai->right = node->left;
        }

        node_destroy(node, bt->key_destroy_fn, bt->val_destroy_fn);
    }

    // Caso 4: nó com dois filhos
    else {
        Node *sucessor_parent = node;
        Node *sucessor = node->right;
    
        // Encontra o sucessor (menor nó da subárvore direita)
        while (sucessor->left != NULL) {
            sucessor_parent = sucessor;
            sucessor = sucessor->left;
        }
    
        // Salva a chave e o valor do sucessor
        void *sucessor_key = sucessor->key;
        void *sucessor_val = sucessor->val;
    
        // Remove o sucessor sem destruir chave/valor
        if (sucessor_parent == node) {
            sucessor_parent->right = sucessor->right;
        } else {
            sucessor_parent->left = sucessor->right;
        }
        free(sucessor);
    
        // Destrói os valores antigos do nó atual
        bt->key_destroy_fn(node->key);
        bt->val_destroy_fn(node->val);
    
        // Atualiza o nó atual com os valores do sucessor
        node->key = sucessor_key;
        node->val = sucessor_val;
    }
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL) {
        return NULL; 
    }

    Node *current = bt->root;
    Node *parent = NULL;

    while (current->left != NULL){
        parent = current;
        current = current->left;
    }

    KeyValPair *pair = malloc(sizeof(KeyValPair));
    pair->key = current->key;
    pair->value = current->val;

    if (parent == NULL){
      
        bt->root = current->right; 
    }
    else{
        parent->left = current->right;  
    }

    free(current);

    return pair;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
    if (bt == NULL || bt->root == NULL) {
        return NULL;
    }

    Node *current = bt->root;
    Node *parent = NULL;

    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }

    KeyValPair *pair = malloc(sizeof(KeyValPair));
    pair->key = current->key;
    pair->value = current->val;

    if (parent == NULL) {
        bt->root = current->left;  
    }
    else{
        parent->right = current->left;  
    }

    free(current);

    return pair;
}

int binary_tree_empty(BinaryTree *bt) {
    return bt->root == NULL;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt) {
    if (bt == NULL || bt->root == NULL) {
        return vector_construct(); // Retorna vetor vazio se a árvore for nula/vazia
    }

    Vector *output = vector_construct(); // Vetor de KeyValPair
    Vector *queue = vector_construct(); // Fila de nós
    vector_push_back(queue, bt->root); // Inicia com a raiz

    while (vector_size(queue) > 0) {
        Node *current = vector_pop_front(queue); // Desenfileira o nó atual

        // Cria um KeyValPair e adiciona ao vetor de saída
        KeyValPair *kvp = key_val_pair_construct(current->key, current->val);
        vector_push_back(output, kvp);

        // Enfileira apenas filhos não nulos
        if (current->left != NULL) {
            vector_push_back(queue, current->left);
        }
        if (current->right != NULL) {
            vector_push_back(queue, current->right);
        }
    }

    vector_destroy(queue); // Libera a fila
    return output;
}

void inorder_recursive(Node *node, Vector *v) {
    if (node == NULL) return;
    inorder_recursive(node->left, v); // Visita esquerda
    KeyValPair *kvp = key_val_pair_construct(node->key, node->val);
    vector_push_back(v, kvp); // Visita raiz
    inorder_recursive(node->right, v); // Visita direita
}

// Travessia in-order (esquerda, raiz, direita)
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
    vector_push_back(v, kvp); // Visita raiz
    preorder_recursive(node->left, v); // Visita esquerda
    preorder_recursive(node->right, v); // Visita direita
}

// Travessia pre-order (raiz, esquerda, direita)
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Vector *v = vector_construct();
    if (bt != NULL && bt->root != NULL) {
        preorder_recursive(bt->root, v);
    }
    return v;
}

void postorder_recursive(Node *node, Vector *v) {
    if (node == NULL) return;
    postorder_recursive(node->left, v); // Visita esquerda
    postorder_recursive(node->right, v); // Visita direita
    KeyValPair *kvp = key_val_pair_construct(node->key, node->val);
    vector_push_back(v, kvp); // Visita raiz
}

// Travessia post-order (esquerda, direita, raiz)
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Vector *v = vector_construct();
    if (bt != NULL && bt->root != NULL) {
        postorder_recursive(bt->root, v);
    }
    return v;
}

void binary_tree_destroy_recursive(BinaryTree *bt, Node *node) {
    // Se o nó já estiver vazio, sai (já encerrou o ramo por aqui)
    if (node == NULL) {
        return;
    }

    // Se não retornou, tenta avançar ainda mais pra esquerda
    binary_tree_destroy_recursive(bt, node->left);

    // Depois, quando concluído os filhos da esquerda, vai pro da direita
    binary_tree_destroy_recursive(bt, node->right);

    // Destrói o nó
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
        printf("NULL");
        return;
    }

    printf("(%d, ", *(int *)node->key);
    binary_tree_print_recursive(node->left);
    printf(", ");
    binary_tree_print_recursive(node->right);
    printf(")");
}

void binary_tree_print(BinaryTree *bt) {
    if (bt == NULL) return;
    binary_tree_print_recursive(bt->root);
    printf("\n");
}