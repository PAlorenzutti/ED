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

        fscanf(file, "%s %s %d %d", nickname, nome, &vencidas, &disputadas);

        Jogador *jogador = jogador_construct(nickname, nome, vencidas, disputadas);

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

void min_jogador(BinaryTree* bt){
    Jogador* jogador = (Jogador*)binary_tree_min(bt);

    if(jogador == NULL){
        printf("Jogador nao encontrado\n");
    }else{
         printf("%s\n", get_nickname_jogador(jogador));
    }
}

void max_jogador(BinaryTree* bt){
    Jogador* jogador = (Jogador*)binary_tree_max(bt);

    if(jogador == NULL){
        printf("Jogador nao encontrada\n");
    }else{
         printf("%s\n", get_nickname_jogador(jogador));
    }
}

void sorted_jogadores(BinaryTree* bt){
    Vector* v = binary_tree_inorder_traversal_recursive(bt);

    for(int i = 0; i< vector_size(v); i++){
        KeyValPair* j = (KeyValPair*)vector_get(v, i);
        Jogador* jogador = (Jogador*)key_val_pair_get_val(j);

        printf("%s %.2f\n", get_nickname_jogador(jogador), get_percentual_vitorias_jogador(jogador));

        key_val_pair_destroy(j);
    }

    vector_destroy(v);
}

void update_victories(HashTable* h, BinaryTree* bt){
    char nickname[MAX_NICKNAME_LENGTH];
    float novo_valor;
    scanf(" %31s %f", nickname, &novo_valor);

    Jogador* jogador = (Jogador*)hash_table_get(h, nickname);

    if(jogador == NULL){
        printf("Jogador nao encontrada\n");
        return;
    }

    binary_tree_remove(bt, jogador);

    update_vitorias_jogador(jogador, novo_valor);

    binary_tree_add(bt, jogador, jogador);
}

void update_defeats(HashTable* h, BinaryTree* bt){
    char nickname[MAX_NICKNAME_LENGTH];
    float novo_valor;
    scanf(" %31s %f", nickname, &novo_valor);

    Jogador* jogador = (Jogador*)hash_table_get(h, nickname);

    if(jogador == NULL){
        printf("Jogador nao encontrada\n");
        return;
    }

    binary_tree_remove(bt, jogador);

    update_derrotas_jogador(jogador, novo_valor);

    binary_tree_add(bt, jogador, jogador);
}

void remove_jogador(HashTable* h, BinaryTree* bt){
    char nickname[MAX_NICKNAME_LENGTH];
    scanf(" %31s", nickname);

    Jogador* jogador = (Jogador*)hash_table_pop(h, nickname);

    if(jogador == NULL){
        printf("Jogador nao encontrada\n");
        return;
    }

    binary_tree_remove(bt, jogador);

    jogador_destroy(jogador);
}

void interval_jogadores(BinaryTree* bt){
    float min, max;
    scanf(" %f %f", &min, &max);

    Vector* v = binary_tree_inorder_traversal_recursive(bt);

    for(int i = 0; i < vector_size(v); i++){
        KeyValPair* pair = (KeyValPair*)vector_get(v,i);
        Jogador* jogador = (Jogador*)key_val_pair_get_val(pair);

        float val = get_percentual_vitorias_jogador(jogador);

        if(val >= min && val <= max){
            printf("%s\n", get_nickname_jogador(jogador));
        }

        key_val_pair_destroy(pair);
    }

    vector_destroy(v);
}

void match_jogador(HashTable* h, BinaryTree* bt) {
    char nickname[MAX_NICKNAME_LENGTH];
    scanf(" %31s", nickname);

    Jogador* jogador = (Jogador*)hash_table_get(h, nickname);

    if(jogador == NULL){
        printf("Jogador nao encontrada\n");
        return;
    }

    Jogador *proximo = (Jogador*)binary_tree_get_nearest(bt, jogador, diff_percentual_vitorias);

    if(proximo == NULL){
        printf("Nao ha jogadores suficientes\n");
        return;
    }
    
    printf("%s\n", get_nickname_jogador(proximo));
}

void operacoes(HashTable* h, BinaryTree* bt){
    char op[9];
    scanf("%8s", op);

    if(strcmp(op, "GET") == 0){
       get_jogador(h);
    }

    if(strcmp(op, "MIN") == 0){
        min_jogador(bt);
    }

    if(strcmp(op, "MAX") == 0){
        max_jogador(bt);
    }

    if(strcmp(op, "SORTED") == 0){
        sorted_jogadores(bt);
    }

    if(strcmp(op, "VICTORIES") == 0){
        update_victories(h, bt);
    }

    if(strcmp(op, "DEFEATS") == 0){
        update_defeats(h, bt);
    }

    if(strcmp(op, "RM") == 0){
        remove_jogador(h, bt);
    }

    if(strcmp(op, "INTERVAL") == 0){
        interval_jogadores(bt);
    }

    if(strcmp(op, "MATCH") == 0){
        match_jogador(h, bt);
    }
}

int main(){
    BinaryTree* bt = binary_tree_construct(compara_jogadores, jogador_destroy, jogador_destroy);

    HashTable* h = hash_table_construct(23, hash_jogador, compara_string);

    leitura_arquivo(h, bt);

    // binary_tree_print(bt, print_jogador);

    // printf("\n");

    printf("\nANTES:\n");

    hash_table_print(h, print_jogador);

    printf("\n");

    int m;
    scanf("%d\n", &m);

    for(int i = 0; i<m; i++){
        operacoes(h, bt);
    }

    // printf("\nDEPOIS:\n");

    // hash_table_print(h, print_jogador);

    // printf("\n");

    hash_table_destroy(h);
    binary_tree_destroy(bt);

    return 0;

}