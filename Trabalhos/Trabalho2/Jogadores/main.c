#include "binary_tree.h"
#include "hash.h"
#include "vector.h"
#include "jogador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leitura_arquivo(HashTable *h, BinaryTree *bt)
{
    char arquivo[100];
    scanf("%99s", arquivo);

    FILE *file = fopen(arquivo, "r");

    int n;
    fscanf(file, "%d", &n);

    for(int i = 0; i < n; i++){
        char *nickname = (char *)malloc((MAX_NICKNAME_LENGTH + 1) * sizeof(char));
        char *nome = (char *)malloc((MAX_NOME_LENGTH + 1) * sizeof(char));
        int disputadas, vencidas;

        fscanf(file, "%s %s %d %d", nickname, nome, &disputadas, &vencidas);

        Jogador *jogador = jogador_construct(nickname, nome, disputadas, vencidas);

        free(nickname);
        free(nome);

        hash_table_set(h, get_nickname_jogador(jogador), jogador);

        binary_tree_add(bt, jogador, jogador);
    }

    fclose(file);
}

void get_jogador(HashTable *h)
{
    char nickname[MAX_NICKNAME_LENGTH];
    scanf(" %99s", nickname);

    Jogador *jogador = (Jogador *)hash_table_get(h, nickname);

    if (jogador == NULL){
        printf("Jogador nao encontrada\n");
    }else{
        print_jogador(jogador);
    }
}

// void min_empresa(BinaryTree* bt){
//     Jogador* jogador = (Jogador*)binary_tree_min(bt);

//     if(jogador == NULL){
//         printf("Jogador nao encontrada\n");
//     }else{
//          printf("%s\n", get_sigla_empresa(jogador));
//     }
// }

// void max_empresa(BinaryTree* bt){
//     Jogador* jogador = (Jogador*)binary_tree_max(bt);

//     if(jogador == NULL){
//         printf("Jogador nao encontrada\n");
//     }else{
//          printf("%s\n", get_sigla_empresa(jogador));
//     }
// }

// void sorted_empresas(BinaryTree* bt){
//     Vector* v = binary_tree_inorder_traversal_recursive(bt);

//     for(int i = 0; i< vector_size(v); i++){
//         KeyValPair* e = (KeyValPair*)vector_get(v, i);
//         Jogador* jogador = (Jogador*)key_val_pair_get_val(e);

//         printf("%s %.2f\n", get_sigla_empresa(jogador), get_valor_unitario_empresa(jogador));

//         key_val_pair_destroy(e);
//     }

//     vector_destroy(v);
// }

// void update_empresa(HashTable* h, BinaryTree* bt){
//     char nickname[MAX_SIGLA_LENGTH];
//     float novo_valor;
//     scanf(" %31s %f", nickname, &novo_valor);

//     Jogador* jogador = (Jogador*)hash_table_get(h, nickname);

//     if(jogador == NULL){
//         printf("Jogador nao encontrada\n");
//         return;
//     }

//     binary_tree_remove(bt, jogador);

//     update_valor_unitario_empresa(jogador, novo_valor);

//     binary_tree_add(bt, jogador, jogador);
// }

// void remove_empresa(HashTable* h, BinaryTree* bt){
//     char nickname[MAX_SIGLA_LENGTH];
//     scanf(" %31s", nickname);

//     Jogador* jogador = (Jogador*)hash_table_pop(h, nickname);

//     if(jogador == NULL){
//         printf("Jogador nao encontrada\n");
//         return;
//     }

//     binary_tree_remove(bt, jogador);

//     empresa_destroy(jogador);
// }

// void empresa_interval(BinaryTree* bt){
//     float min, max;
//     scanf(" %f %f", &min, &max);

//     Vector* v = binary_tree_inorder_traversal_recursive(bt);

//     for(int i = 0; i < vector_size(v); i++){
//         KeyValPair* pair = (KeyValPair*)vector_get(v,i);
//         Jogador* jogador = (Jogador*)key_val_pair_get_val(pair);
//         float val = get_valor_unitario_empresa(jogador);

//         if(val >= min && val <= max){
//             printf("%s\n", get_sigla_empresa(jogador));
//         }

//         key_val_pair_destroy(pair);
//     }

//     vector_destroy(v);
// }

void operacoes(HashTable* h, BinaryTree* bt){
    char op[9];
    scanf("%8s", op);

    if(strcmp(op, "GET") == 0){
       get_jogador(h);
    }

    // if(strcmp(op, "MIN") == 0){
    //     min_empresa(bt);
    // }

    // if(strcmp(op, "MAX") == 0){
    //     max_empresa(bt);
    // }

    // if(strcmp(op, "SORTED") == 0){
    //     sorted_empresas(bt);
    // }

    // if(strcmp(op, "UPDATE") == 0){
    //     update_empresa(h, bt);
    // }

    // if(strcmp(op, "RM") == 0){
    //     remove_empresa(h, bt);
    // }

    // if(strcmp(op, "INTERVAL") == 0){
    //     empresa_interval(bt);
    // }
}

int main(){
    BinaryTree* bt = binary_tree_construct(compara_jogadores, jogador_destroy, jogador_destroy);

    HashTable* h = hash_table_construct(23, hash_jogador, compara_string);

    leitura_arquivo(h, bt);

    // binary_tree_print(bt, print_jogador);

    // printf("\n");

    // hash_table_print(h, print_jogador);

    int m;
    scanf("%d\n", &m);

    for(int i = 0; i<m; i++){
        operacoes(h, bt);
    }

    hash_table_destroy(h);
    binary_tree_destroy(bt);

    return 0;

}