#ifndef EMPRESA_H_
#define EMPRESA_H_

#include "hash.h"

#define MAX_NAME_LENGTH 100
#define MAX_SIGLA_LENGTH 32

typedef struct Empresa Empresa;

Empresa* empresa_construct(char *nome, char *sigla, float valor_unitario, int total_acoes, int acoes_vendidas);

int compara_empresas(void *empresa_1, void *empresa_2);

int compara_string(void *key1, void *key2);

int hash_empresa(HashTable *h, void *key) ;

void print_empresa(void *empresa);

void empresa_destroy(void *e);

#endif