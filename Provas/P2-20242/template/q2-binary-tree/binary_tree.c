
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

struct BinaryTree
{
    Node *root;
};


Node *node_construct(int value, Node *left, Node *right)
{
    Node *node = calloc(1, sizeof(Node));

    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}


void node_destroy(Node *node)
{
    free(node);
}


BinaryTree *binary_tree_construct()
{
    BinaryTree *bt = calloc(1, sizeof(BinaryTree));
    bt->root = NULL;
    return bt;
}


void binary_tree_add(BinaryTree *bt, int value)
{
    Node *new_node = node_construct(value, NULL, NULL);

    if (bt->root == NULL)
        bt->root = new_node;
    else
    {
        Node *node = bt->root;

        while (node != NULL)
        {
            if (value == node->value)
            {
                node_destroy(new_node);
                return;
            }
            else if (value < node->value)
            {
                if (node->left == NULL)
                {
                    node->left = new_node;
                    return;
                }
                else
                    node = node->left;
            }
            else
            {
                if (node->right == NULL)
                {
                    node->right = new_node;
                    return;
                }
                else
                    node = node->right;
            }
        }
    }
}


void _destroy_node_recursive(Node *node)
{
    if (node == NULL)
        return;

    _destroy_node_recursive(node->left);
    _destroy_node_recursive(node->right);
    node_destroy(node);
}


void binary_tree_destroy(BinaryTree *bt)
{
    _destroy_node_recursive(bt->root);
    free(bt);
}


void _percurso(Node *node, int x, int k, int min, int max, int *out_array, int *out_array_size) {
    if(node == NULL){
        return;
    } 

    //visita primeiro até o mínimo;
    _percurso(node->left, x, k, min, max, out_array, out_array_size);

    //se o valor estiver dentro do intervalo, entra;
    if (node->value >= min && node->value <= max) {
        //se o array não tiver completo, adiciona o valor ao array;
        if (*out_array_size < k) {
            out_array[*out_array_size] = node->value;
            (*out_array_size)++;
        } else {
            //se o array tiver completo, faz a diferença entre ele e o valor e compara com as diferenças que já estão no vetor;

            //diferença entre o atual e o nó;
            int diff_atual = abs(node->value - x);

            //diferença entre o primeiro nó adicionado e o nó;
            int diff_first = abs(out_array[0] - x);

            //diferença entre o último nó adicionado e o nó;
            int diff_last = abs(out_array[k - 1] - x);

            //compara as diferenças;
            int diff_max;
                if (diff_first > diff_last) {
                    diff_max = diff_first;
                } else {
                    diff_max = diff_last;
                }

            //se a diferença atual for menor que a maior diferença que tá no vetor;
            if (diff_atual < diff_max) {
                //se a primeira diferença for maior que a última diferença, adiciona a diferença atual na última posição
                if(diff_first > diff_last){
                    for (int i = 0; i < k - 1; ++i) {
                        out_array[i] = out_array[i + 1];
                    }
                }
                
                out_array[k - 1] = node->value;
            }
        }
    }

    //depois de percorrer à esquerda, vai o máximo pra direita;
    _percurso(node->right, x, k, min, max, out_array, out_array_size);
}


int* binary_tree_knn(BinaryTree *bt, int x, int k, int min, int max, int *out_array_size)
{
    // o vetor de vizinhos mais proximos pode conter ate k valores, onde k eh
    // frequentemente menor que o numero de elementos na arvore.
    int *out_array = (int *) calloc(k, sizeof(int));

    // o tamanho do vetor de saida eh inicialmente zero e deve ser
    // atualizado quando novos vizinhos forem adicionados ou removidos.
    *out_array_size = 0;

    // funcao principal que itera sobre os elementos da arvore, verifica se
    // eles estao no intervalo e atualiza as variaveis out_array e out_array_size.
    _percurso(bt->root, x, k, min, max, out_array, out_array_size);

    return out_array;
}
