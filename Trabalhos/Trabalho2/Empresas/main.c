#include "empresa.h"
#include "vector.h"
#include "hash.h"
#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leitura_arquivo(HashTable *h, BinaryTree *bt){
    //leitura do arquivo;
    char filename[100];
    scanf("%99s", filename);

    FILE *file = fopen(filename, "r");

    int n;
    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) {
        char *nome = (char*)malloc((MAX_NAME_LENGTH + 1) * sizeof(char));
        char *sigla = (char*)malloc((MAX_SIGLA_LENGTH + 1) * sizeof(char));
        float valor_unitario;
        int total_acoes, acoes_vendidas;

        fscanf(file, "%s %s %f %d %d", nome, sigla, &valor_unitario, &total_acoes, &acoes_vendidas);

        Empresa *e = empresa_construct(nome, sigla, valor_unitario, total_acoes, acoes_vendidas);

        //libera as strings alocadas
        free(nome);
        free(sigla);

        //adiciona na tabela hash (sigla como chave, empresa como valor);
        hash_table_set(h, get_sigla_empresa(e), e);

        //adiciona na árvore binária (empresa como par chave-valor);
        binary_tree_add(bt, e, e);
    }

    fclose(file);
}

void get_empresa(HashTable *h){
    char sigla[MAX_SIGLA_LENGTH];
    scanf(" %31s", sigla);

    Empresa *e = (Empresa*)hash_table_get(h, sigla);

    if(e == NULL){
        printf("Empresa nao encontrada\n");
    }else{
        print_empresa(e);
    }
}

void min_empresa(BinaryTree *bt){
    Empresa *e = (Empresa*)binary_tree_min(bt);

    if(e == NULL){
        printf("Empresa nao encontrada\n");
    }else{
        //printa o nome da empresa
        printf("%s\n", get_sigla_empresa(e));
    }
}

void max_empresa(BinaryTree *bt){
    Empresa *e = (Empresa*)binary_tree_max(bt);

    if(e == NULL){
        printf("Empresa nao encontrada\n");
    }else{
        //printa o nome da empresa;
        printf("%s\n", get_sigla_empresa(e));
    }
}

void sorted_empresas(BinaryTree *bt){
    Vector *v = binary_tree_inorder_traversal_recursive(bt);

    for(int i = 0; i < vector_size(v); i++){
        KeyValPair *e = (KeyValPair*)vector_get(v, i);
        Empresa *empresa = (Empresa*)key_val_pair_get_val(e);
        
        //printa a sigla da empresa e seu valor unitário por ação;
        printf("%s %.2f\n", get_sigla_empresa(empresa), get_valor_unitario(empresa));

        key_val_pair_destroy(e);
    }

    vector_destroy(v);
}

void operacoes(HashTable *h, BinaryTree *bt){
    char op[9];
    scanf("%8s", op);

    //pegar a empresa a partir da sigla;
    if(strcmp(op, "GET") == 0){
       get_empresa(h);
    }

    //pegar a empresa com o menor valor unitário na árvore;
    if(strcmp(op, "MIN") == 0){
        min_empresa(bt);
    }

    //pegar a empresa com o maior valor unitário na árvore;
    if(strcmp(op, "MAX") == 0){
        max_empresa(bt);
    }

    if(strcmp(op, "SORTED") == 0){
        sorted_empresas(bt);
    }
}

int main() {
    //criar árvore binária com o preço unitário das ações como critério primário de ordenação, em caso de empate, ordem alfabética da sigla;
    BinaryTree *bt = binary_tree_construct(compara_empresas, empresa_destroy, empresa_destroy);

    //criar tabela hash usando a sigla como chave e a empresa como valor;
    HashTable *h = hash_table_construct(23, hash_empresa, compara_string);

    //leitura do arquivo
    leitura_arquivo(h, bt);

    //operações
    int m;
    scanf("%d\n", &m);

    binary_tree_print(bt, print_empresa);

    for(int i = 0; i < m; i++){
        operacoes(h, bt);
    }

    //liberar memória  
    hash_table_destroy(h);
    binary_tree_destroy(bt);
    
    return 0;
}