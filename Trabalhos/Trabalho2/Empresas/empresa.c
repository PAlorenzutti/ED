#include "empresa.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Empresa{
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

void print_empresa(Empresa *e){
    printf("%s %s %.2f %d %d\n", e->nome, e->sigla, e->valor_unitario, e->total_acoes, e->acoes_vendidas);
}

void empresa_destroy(Empresa *e){
    free(e);
}