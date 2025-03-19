#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include "hash.h"

#define MAX_NICKNAME_LENGTH 100
#define MAX_NOME_LENGTH 100

typedef struct Jogador Jogador;

Jogador* jogador_construct(char *nickname, char* nome, int disputadas, int vencidas);

char* get_nickname_jogador(Jogador* j);

float get_percentual_vitorias_jogador(Jogador* j);

void update_vitorias_jogador(Jogador* j, int novo_valor);

void update_derrotas_jogador(Jogador* j, int novo_valor);

float diff_percentual_vitorias(void *jogador_1, void *jogador_2);

int hash_jogador(HashTable *h, void *key);

int compara_string(void *key1, void *key2);

int compara_jogadores(void *jogador_1, void *jogador_2);

void print_jogador(void *j);

void jogador_destroy(void* j);

#endif