#ifndef EMPRESA_H_
#define EMPRESA_H_

#define MAX_NAME_LENGTH 100
#define MAX_SIGLA_LENGTH 32

typedef struct Empresa Empresa;

Empresa* empresa_construct(char *nome, char *sigla, float valor_unitario, int total_acoes, int acoes_vendidas);

void print_empresa(Empresa *e);

void empresa_destroy(Empresa *e);

#endif