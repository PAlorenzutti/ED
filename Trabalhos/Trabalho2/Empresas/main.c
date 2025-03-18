#include "binary_tree.h"
#include "hash.h"
#include "vector.h"
#include "empresa.h"

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
        char *nome = (char *)malloc((MAX_NAME_LENGTH + 1) * sizeof(char));
        char *sigla = (char *)malloc((MAX_SIGLA_LENGTH + 1) * sizeof(char));
        float valor_unitario;
        int total_acoes, acoes_vendidas;

        fscanf(file, "%s %s %f %d %d", nome, sigla, &valor_unitario, &total_acoes, &acoes_vendidas);

        Empresa *empresa = empresa_construct(nome, sigla, valor_unitario, total_acoes, acoes_vendidas);

        free(nome);
        free(sigla);

        hash_table_set(h, get_sigla_empresa(empresa), empresa);

        binary_tree_add(bt, empresa, empresa);
    }

    fclose(file);
}

void get_empresa(HashTable *h)
{
    char sigla[MAX_SIGLA_LENGTH];
    scanf(" %31s", sigla);

    Empresa *empresa = (Empresa *)hash_table_get(h, sigla);

    if (empresa == NULL){
        printf("Empresa nao encontrada\n");
    }else{
        print_empresa(empresa);
    }
}

void min_empresa(BinaryTree* bt){
    Empresa* empresa = (Empresa*)binary_tree_min(bt);

    if(empresa == NULL){
        printf("Empresa nao encontrada\n");
    }else{
         printf("%s\n", get_sigla_empresa(empresa));
    }
}

void max_empresa(BinaryTree* bt){
    Empresa* empresa = (Empresa*)binary_tree_max(bt);

    if(empresa == NULL){
        printf("Empresa nao encontrada\n");
    }else{
         printf("%s\n", get_sigla_empresa(empresa));
    }
}

void sorted_empresas(BinaryTree* bt){
    Vector* v = binary_tree_inorder_traversal_recursive(bt);

    for(int i = 0; i< vector_size(v); i++){
        KeyValPair* e = (KeyValPair*)vector_get(v, i);
        Empresa* empresa = (Empresa*)key_val_pair_get_val(e);

        printf("%s %.2f\n", get_sigla_empresa(empresa), get_valor_unitario_empresa(empresa));

        key_val_pair_destroy(e);
    }

    vector_destroy(v);
}

void update_empresa(HashTable* h, BinaryTree* bt){
    char sigla[MAX_SIGLA_LENGTH];
    float novo_valor;
    scanf(" %31s %f", sigla, &novo_valor);

    Empresa* empresa = (Empresa*)hash_table_get(h, sigla);

    if(empresa == NULL){
        printf("Empresa nao encontrada\n");
        return;
    }

    binary_tree_remove(bt, empresa);

    update_valor_unitario_empresa(empresa, novo_valor);

    binary_tree_add(bt, empresa, empresa);
}

void remove_empresa(HashTable* h, BinaryTree* bt){
    char sigla[MAX_SIGLA_LENGTH];
    scanf(" %31s", sigla);

    Empresa* empresa = (Empresa*)hash_table_pop(h, sigla);

    if(empresa == NULL){
        printf("Empresa nao encontrada\n");
        return;
    }

    binary_tree_remove(bt, empresa);

    empresa_destroy(empresa);
}

void empresa_interval(BinaryTree* bt){
    float min, max;
    scanf(" %f %f", &min, &max);

    Vector* v = binary_tree_inorder_traversal_recursive(bt);

    for(int i = 0; i < vector_size(v); i++){
        KeyValPair* pair = (KeyValPair*)vector_get(v,i);
        Empresa* empresa = (Empresa*)key_val_pair_get_val(pair);
        float val = get_valor_unitario_empresa(empresa);

        if(val >= min && val <= max){
            printf("%s\n", get_sigla_empresa(empresa));
        }

        key_val_pair_destroy(pair);
    }

    vector_destroy(v);
}

void operacoes(HashTable* h, BinaryTree* bt){
    char op[9];
    scanf("%8s", op);

    if(strcmp(op, "GET") == 0){
       get_empresa(h);
    }

    if(strcmp(op, "MIN") == 0){
        min_empresa(bt);
    }

    if(strcmp(op, "MAX") == 0){
        max_empresa(bt);
    }

    if(strcmp(op, "SORTED") == 0){
        sorted_empresas(bt);
    }

    if(strcmp(op, "UPDATE") == 0){
        update_empresa(h, bt);
    }

    if(strcmp(op, "RM") == 0){
        remove_empresa(h, bt);
    }

    if(strcmp(op, "INTERVAL") == 0){
        empresa_interval(bt);
    }
}

int main(){
    BinaryTree* bt = binary_tree_construct(compara_empresas, empresa_destroy, empresa_destroy);

    HashTable* h = hash_table_construct(23, hash_empresa, compara_string);

    leitura_arquivo(h, bt);

    int m;
    scanf("%d\n", &m);

    for(int i = 0; i<m; i++){
        operacoes(h, bt);
    }

    hash_table_destroy(h);
    binary_tree_destroy(bt);

    return 0;

}