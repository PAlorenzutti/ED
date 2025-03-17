#ifndef EMPRESA_H_
#define EMPRESA_H_

#include "hash.h"

#define MAX_NAME_LENGTH 100
#define MAX_SIGLA_LENGTH 32

typedef struct Empresa Empresa;

Empresa* empresa_construct(char *nome, char *sigla, float valor_unitario, int total_acoes, int acoes_vendidas);

char *get_nome_empresa(Empresa *e);

char *get_sigla_empresa(Empresa *e);

float get_valor_unitario_empresa(Empresa *e);

int get_total_acoes_empresa(Empresa *e);

int get_acoes_vendidas_empresa(Empresa *e);

void update_valor_unitario_empresa(Empresa *e, float novo_valor);

int compara_empresas(void *empresa_1, void *empresa_2);

int compara_string(void *key1, void *key2);

int hash_empresa(HashTable *h, void *key) ;

void print_empresa(void *empresa);

void empresa_destroy(void *e);

#endif