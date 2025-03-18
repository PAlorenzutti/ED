#include "empresa.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Empresa {
    char nome[MAX_NAME_LENGTH];
    char sigla[MAX_SIGLA_LENGTH];
    float valor_unitario;
    int total_acoes;
    int acoes_vendidas;
};

Empresa* empresa_construct(char *nome, char *sigla, float valor_unitario, int total_acoes, int acoes_vendidas){
    Empresa *e = (Empresa*)malloc(sizeof(Empresa));

    strncpy(e->nome, nome, MAX_NAME_LENGTH);
    e->nome[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(e->sigla, sigla, MAX_SIGLA_LENGTH);
    e->sigla[MAX_SIGLA_LENGTH - 1] = '\0';

    e->valor_unitario = valor_unitario;
    e->total_acoes = total_acoes;
    e->acoes_vendidas = acoes_vendidas;

    return e;
}

char *get_nome_empresa(Empresa *e){
    return e->nome;
}

char *get_sigla_empresa(Empresa *e){
    return e->sigla;
}

float get_valor_unitario_empresa(Empresa *e){
    return e->valor_unitario;
}

int get_total_acoes_empresa(Empresa *e){
    return e->total_acoes;
}

int get_acoes_vendidas_empresa(Empresa *e){
    return e->acoes_vendidas;
}

void update_valor_unitario_empresa(Empresa *e, float novo_valor){
    e->valor_unitario = novo_valor;
}

int compara_string(void *key1, void *key2) {
    char *str1 = (char *)key1;
    char *str2 = (char *)key2;
   
    return strcmp(str1, str2);
}

int hash_empresa(HashTable *h, void *key) {
    char *str = (char*)key;
    int size = hash_table_size(h);
    int base = 31;
    long hash_val = 0;
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        hash_val = (hash_val * base + str[i]) % size;
    }

    hash_val = hash_val % size;
    if (hash_val < 0) {
        hash_val += size;
    }

    return hash_val;
}

int compara_empresas(void *empresa_1, void *empresa_2) {
    Empresa *e1 = (Empresa*)empresa_1;
    Empresa *e2 = (Empresa*)empresa_2;

    if (e1->valor_unitario == e2->valor_unitario) {
        return strcmp(e1->sigla, e2->sigla);
    }

    return (e1->valor_unitario > e2->valor_unitario) ? 1 : -1;
}

void print_empresa(void *empresa) {
    Empresa *e = (Empresa*)empresa;

    printf("%s %s %.2f %d %d\n", e->nome, e->sigla, e->valor_unitario, e->total_acoes, e->acoes_vendidas);
}

void empresa_destroy(void *e) {
    Empresa *empresa = (Empresa*)e;
    
    free(empresa);
}
